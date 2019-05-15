#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


void* thread_run1(void *val){
    printf("Thread1 is running!\n");
    printf("%s:pid is %d, tid is %llu\n",
        (char*)val,(int)getpid(),(unsigned long long)pthread_self());
    sleep(-1);
    return NULL;
}

void* thread_run2(void *val){
    printf("Thread2 is running!\n");
    printf("%s:pid is %d, tid is %llu\n",
        (char*)val,(int)getpid(),(unsigned long long)pthread_self());
    sleep(-1);
    return NULL;
}

int main(){
    pthread_t pid1,pid2;
    if(pthread_create(&pid1,NULL,thread_run1,"Thread1")!=0){
        printf("failed to create thread1!\n");
        return -1;
    }
    if(pthread_create(&pid2,NULL,thread_run2,"Thread2")!=0){
        printf("failed to create thread2!\n");
        return -1;
    }

    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    return 0;
}