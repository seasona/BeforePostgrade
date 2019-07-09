// 测试unix下进程通信使用的三种方式之一管道通信pipe
// 头文件: <unistd.h>
// int pipe(int filedes[2]);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int result = -1;
    int fd[2];
    int nbytes;
    pid_t pid;
    char string[] = "Try to use a pipe";
    char read_buffer[100];

    int *read_fd = &fd[0];
    int *write_fd = &fd[1];

    // 函数调用成功返回r/w两个文件描述符。无需open，但需手动close。
    // 规定：fd[0]->r； fd[1]->w，就像0对应标准输入，1对应标准输出一样。
    // 向管道文件读写数据其实是在读写内核缓冲区。
    // 管道创建成功以后，创建该管道的进程（父进程）同时掌握着管道的读端和写端
    result = pipe(fd);
    if (result == -1) {
        printf("fail to create pipe\n");
        return -1;
    }

    // fork一个子进程出来，子进程的pid为0，父进程的pid为子进程的进程序号
    pid = fork();

    if (pid == -1) {
        printf("fail to fork\n");
        return -1;
    } else if (pid == 0) {
        // 关闭子进程的read
        close(*read_fd);
        result = write(*write_fd, string, strlen(string));
        return 0;
    } else {
        // 关闭父进程的write
        // 形成了子进程->管道->父进程的半双工通信
        close(*write_fd);
        nbytes = read(*read_fd, read_buffer, sizeof(read_buffer));
        printf("the parent receive %d bytes data: %s\n", nbytes, read_buffer);
    }

    return 0;
}
