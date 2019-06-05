//一个简单selec函数的demo，文件描述符为标准输入0

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    //文件描述符集合rd
    fd_set rd;
    struct timeval tv;
    int err;

    //将文件描述符集中有关位设为1
    //比如此时是将标准输入0有关位设为1
    FD_ZERO(&rd);
    FD_SET(0, &rd);

    //设置超时为10s
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    //select中的文件描述符是上界[0,n)
    err = select(1, &rd, NULL, NULL, &tv);

    if (err == 0)
    {
        printf("select time run out!\n");
    }
    else if (err == -1)
    {
        printf("failed to select!\n");
    }
    else
    {
        printf("data is available!\n");
    }

    return 0;
}