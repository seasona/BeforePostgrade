#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

//void HelloThread(int threadid)这么写会警告，但是也可以编译通过
void *HelloThread(void *threadid)
{
    int tid = (int)threadid;
    printf("This thread id is: %d\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t threads[NUM_THREADS];
    int i;
    int rc;
    for (i = 0; i < NUM_THREADS; i++)
    {
        printf("main():create thread %d\n", i);
        rc = pthread_create(&threads[i], NULL, HelloThread, (void *)i);
        if (rc)
        {
            printf("Error: failed to create thread %d\n", i);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}