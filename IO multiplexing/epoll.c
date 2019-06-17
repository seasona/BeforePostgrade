//epoll是linux 2.6之后提出的新的一种IO多路复用方式，比起select和poll，在连接数比较
//大的情况下效率更高，

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{
    int flag = 0;
    int epfd, nfds;
    struct epoll_event ev;
    struct epoll_event events[5];

    //int epoll_create(int size);
    //size=1,只需监听一个文件描述符
    epfd = epoll_create(1);

    //注册epoll事件
    //int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    //-fd：要操作的文件描述符
    //-op：指定操作类型
    //-event：指定事件，它是epoll_event结构指针类型
    ev.data.fd = STDIN_FILENO;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);

    while (1)
    {
        if (flag == 1)
        {
            break;
        }

        //int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
        //返回：成功时返回就绪的文件描述符的个数，失败时返回-1并设置errno
        //-events：检测到事件，将所有就绪的事件从内核事件表中复制到它的第二个参数events指向的数组中
        nfds = epoll_wait(epfd, events, 5, -1);
        for (int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == STDIN_FILENO)
            {
                char buf[1024] = {0};
                //读取缓冲区，注意会读入'\n'
                read(STDIN_FILENO, buf, sizeof(buf));

                char buff[1024] = {0};
                for (int i = 0; i < strlen(buf) - 1; i++)
                {
                    buff[i] = buf[i];
                }
                //退出检测
                if (strcmp(buff, "quit") == 0)
                {
                    flag = 1;
                    break;
                }
                printf("welcome to epoll's world!\n");
            }
        }
    }

    return 0;
}