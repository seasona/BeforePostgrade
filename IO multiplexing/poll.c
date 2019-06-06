//poll比起selet更好一些，能用poll就用poll

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

int main(int argc, char **argv)
{
    int i, ret, fd;
    unsigned char keys_val;
    struct pollfd fds[1];

    fd = open("/dev/buttons", 0);
    if (fd < 0)
    {
        printf("Can't open /dev/buttons\n");
        return -1;
    }

    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while (1)
    {
        ret = poll(fds, 1, 5000);
        if (ret == 0)
        {
            printf("time out\n");
        }
        else
        {
            //有响应，读取键值
            read(fd, &keys_val, sizeof(keys_val));
            printf("keys_val = 0x%x\n", keys_val);
        }
    }
    close(fd);
    return 0;
}