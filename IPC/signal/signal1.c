#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// 信号注册函数
// 对于已注册的信号，使用 kill 发送都可以正常接收到，但是如果发送了未注册的信号，则会使得应用程序终止进程。
void handler(int signum){
    if(signum==SIGIO){
        printf("SIGIO signal:%d\n",signum);
    }else if(signum==SIGUSR1){
        printf("SIGUSR1 signal:%d\n",signum);
    }else{
        printf("error\n");
    }
}

int main(){
    signal(SIGIO,handler);
    signal(SIGUSR1,handler);
    printf("SIGIO:%d, SIGUSR1:%d\n",SIGIO,SIGUSR1);
    for(;;){
        sleep(10000);
    }
    return 0;
}