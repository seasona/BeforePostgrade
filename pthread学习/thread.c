#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct ThreadData{
    int thread_id;
    char *message;
};

//运行函数的参数arg必须通过把引用作为指针强制转换为 void 类型进行传递
void *PrintHello(void *threadarg){
    struct ThreadData *my_data;
    my_data=(struct ThreadData*)threadarg;
    printf("Thread ID: %d",my_data->thread_id);
    printf(" Message: %s",my_data->message);

    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    struct ThreadData td[NUM_THREADS];
    int rc;
    int i;

    for(i=0;i<NUM_THREADS;i++){
        printf("main():creating thread, %d\n",i);
        td[i].thread_id=i;
        td[i].message=(char*)"This is message";
        
        rc=pthread_create(&threads[i],NULL,PrintHello,(void *)&td[i]);
        if(rc){
            printf("Error: unable to create thread\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
}