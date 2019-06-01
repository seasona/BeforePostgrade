/*This is a example of using pthread_mutex_t*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double *a;
    double *b;
    double sum;
    int veclen;
} DotData;

#define NUM_PHREADS 4
#define VECLEN 100

DotData dotstr;
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

void *dotprod(void *arg)
{
    int i, start, end, len;
    long offset;
    double mysum, *x, *y;
    offset = *((long *)arg);

    //多线程分别计算每段len中的sum
    len = dotstr.veclen;
    start = offset * len;
    end = start + len;
    x = dotstr.a;
    y = dotstr.b;

    mysum = 0;
    for (i = start; i < end; i++)
    {
        mysum += (x[i] * y[i]);
    }
    printf("Thread %ld's sum =%lf\n", offset, mysum);

    pthread_mutex_lock(&mutexsum);
    dotstr.sum += mysum;
    pthread_mutex_unlock(&mutexsum);

    pthread_exit((void *)0);
}

int main(int argc, char **argv)
{
    long i;
    double *a, *b;
    void *status;

    pthread_t callThd[NUM_PHREADS];
    pthread_attr_t attr;

    a = (double *)malloc(NUM_PHREADS * VECLEN * sizeof(double));
    b = (double *)malloc(NUM_PHREADS * VECLEN * sizeof(double));

    for (i = 0; i < VECLEN * NUM_PHREADS; i++)
    {
        a[i] = 1.0;
        b[i] = i;
    }
    dotstr.veclen = VECLEN;
    dotstr.a = a;
    dotstr.b = b;
    dotstr.sum = 0;

    //pthread_mutex_init(&mutexsum, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUM_PHREADS; i++)
    {
        pthread_create(&callThd[i], &attr, dotprod, (void *)&i);
    }

    for (i = 0; i < NUM_PHREADS; i++)
    {
        pthread_join(callThd[i], &status);
    }

    printf("Sum =%f\n", dotstr.sum);
    free(a);
    free(b);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}