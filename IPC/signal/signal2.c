#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(argc!=3){
        printf("argument error!\n");
        return -1;
    }
    int pid=atoi(argv[1]);
    int sig=atoi(argv[2]);
    if(pid>0&&sig>0){
        kill(pid,sig);
    }else{
        printf("target id and signal number must > 0\n");
    }
    return 0;
}