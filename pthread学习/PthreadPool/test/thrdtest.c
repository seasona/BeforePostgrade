#define THREAD 32
#define QUEUE 256

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "PthreadPool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;

void dummy_task(void *arg) {
    usleep(10000);
    done++;
}

int main(int argc, char **argv) {
    threadpool_t *pool;

    pthread_mutex_init(&lock, NULL);
    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    printf("pool started with %d threads and queue size of %d\n", THREAD,
           QUEUE);

    while (threadpool_add(pool, &dummy_task, NULL, 0) == 0) {
        tasks++;
    }

    printf("Added %d tasks\n", tasks);
    while ((tasks / 2) > done) {
        usleep(100000);
    }
    assert(threadpool_destroy(pool, 0) == 0);
    printf("%d tasks has been done\n", done);
    return 0;
}