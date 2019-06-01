#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_PTHREADS 3
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;

void *inc_count(void *t)
{
    int i;
    long my_id = *((long *)t);

    for (i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        count++;

        if (count == COUNT_LIMIT)
        {
            pthread_cond_signal(&count_threshold_cv);
            printf("inc_count(): thread %ld, count =%d Threshold reached.\n", my_id, count);
        }
        printf("inc_count(): thread %ld, count= %d, unlocking mutex\n", my_id, count);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watch_count(void *t)
{
    long my_id = *((long *)t);
    printf("Starting watch_count(): thread %ld\n", my_id);

    pthread_mutex_lock(&count_mutex);
    while (count < COUNT_LIMIT)
    {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): thread %ld Condition signal received.\n", my_id);
    }
    count += 125;
    printf("watch_count(): thread %ld count now =%d.\n", my_id, count);
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    int i, rc;
    long t1 = 1, t2 = 2, t3 = 3;
    pthread_t threads[3];

    //只要声明了就一定要初始化，否则会段错误
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&threads[0], &attr, watch_count, (void *)&t1);
    pthread_create(&threads[1], &attr, inc_count, (void *)&t2);
    pthread_create(&threads[2], &attr, inc_count, (void *)&t3);

    for (i = 0; i < NUM_PTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    //pthread_mutex_destroy(&count_mutex);
    pthread_exit(NULL);
}
