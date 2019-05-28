//生产者消费者模型

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct msg{
    struct msg *next;
    int num;
};

struct msg *head;
struct msg *mp;

pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

//消费者
void *consumer(void *p){
    while(1){
        pthread_mutex_lock(&lock);
        while(head==NULL){  //使用while而不使用if来避免spurious wakeup
            pthread_cond_wait(&has_product,&lock);
        }
        mp=head;
        head=mp->next;
        printf("Consumer --- %d\n",mp->num);
        free(mp);
        mp=NULL;
        pthread_mutex_unlock(&lock);
    }
}

//生产者
void *producer(void *p){
    while(1){
        pthread_mutex_lock(&lock);
        mp=malloc(sizeof(struct msg));
        mp->num=rand()%1000+1;
        printf("Producer --- %d\n",mp->num);
        mp->next=head;
        head=mp;
        pthread_mutex_unlock(&lock);
        //类似PV操作
        pthread_cond_signal(&has_product);
    }
}

int main(){
    pthread_t pid,cid;
    srand(time(NULL));

    pthread_create(&pid,NULL,producer,NULL);
    pthread_create(&cid,NULL,consumer,NULL);

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    return 0;
}
