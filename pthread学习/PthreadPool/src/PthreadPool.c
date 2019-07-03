#include "PthreadPool.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    immediate_shutdown = 1,  //被动停止
    graceful_shutdown = 2    //主动关闭
} threadpool_shutdown_t;

typedef struct {
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

struct threadpool_t {
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t *threads;
    threadpool_task_t *queue;  //任务队列(循环)
    int thread_count;
    int queue_size;
    int head;   //任务队列的头
    int tail;   //任务队列的尾
    int count;  //待执行的任务数
    int shutdown;
    int started;  //正在运行的线程数
};

static int threadpool_free(threadpool_t *pool);
static void *threadpool_thread(void *threadpool);

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags) {
    threadpool_t *pool;
    int i;
    (void)flags;

    if (thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0 ||
        queue_size > MAX_QUEUE) {
        return NULL;
    }

    if ((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL) {
        return NULL;
    }

    //初始化
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    pool->queue =
        (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);

    if (pthread_mutex_init(&(pool->lock), NULL) != 0 ||
        (pthread_cond_init((&pool->notify), NULL) != 0) ||
        (pool->threads == NULL) || (pool->queue == NULL)) {
        if (pool) {
            threadpool_free(pool);
        }
        return NULL;
    }

    for (i = 0; i < thread_count; i++) {
        if (pthread_create(&(pool->threads[i]), NULL, threadpool_thread,
                           (void *)pool) != 0) {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }
    return pool;
}

int threadpool_add(threadpool_t *pool, void (*function)(void *), void *argument,
                   int flags) {
    int err = 0;
    int next;
    (void)flags;

    if (pool == NULL || function == NULL) {
        return threadpool_invalid;
    }

    if (pthread_mutex_lock(&(pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    next = (pool->tail + 1) % pool->queue_size;

    do {
        if (pool->count == pool->queue_size) {
            err = threadpool_queue_full;
            break;
        }

        if (pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        //新任务进入队列
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->count += 1;

        if (pthread_cond_signal(&(pool->notify)) != 0) {
            err = threadpool_lock_failure;
            break;
        }
    } while (0);

    if (pthread_mutex_unlock(&(pool->lock)) != 0) {
        err = threadpool_lock_failure;
    }

    return err;
}

int threadpool_destroy(threadpool_t *pool, int flags) {
    int i, err = 0;

    if (pool == NULL) {
        return threadpool_invalid;
    }

    if (pthread_mutex_lock((&pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    do {
        if (pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        pool->shutdown = (flags & threadpool_graceful) ? graceful_shutdown
                                                       : immediate_shutdown;

        //唤醒所有线程来进行销毁
        if ((pthread_cond_broadcast(&(pool->notify)) != 0) ||
            (pthread_mutex_unlock(&(pool->lock)) != 0)) {
            err = threadpool_lock_failure;
            break;
        }

        for (i = 0; i < pool->thread_count; i++) {
            if (pthread_join(pool->threads[i], NULL) != 0) {
                err = threadpool_thread_failure;
            }
        }
    } while (0);

    if (!err) {
        threadpool_free(pool);
    }
    return err;
}

static int threadpool_free(threadpool_t *pool) {
    if (pool == NULL || pool->started > 0) {
        return -1;
    }

    if (pool->threads) {
        free(pool->threads);
        free(pool->queue);

        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    free(pool);
    return 0;
}

static void *threadpool_thread(void *threadpool) {
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    while (1) {
        pthread_mutex_lock(&(pool->lock));

        while ((pool->count == 0) && (!pool->shutdown)) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if ((pool->shutdown == immediate_shutdown) ||
            ((pool->shutdown == graceful_shutdown) && (pool->count == 0))) {
            break;
        }

        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        pthread_mutex_unlock(&(pool->lock));

        (*(task.function))(task.argument);
    }
    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return NULL;
}