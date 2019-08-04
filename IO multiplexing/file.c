// linux中自带的文件操作函数，C中比较常用的fopen等就是对这些函数的封装
//也就是系统调用

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // fo是文件描述符，标准输入是0，标准输出是1这样
    int fo = open("./data.txt", O_RDWR);
    if (fo != -1) {
        printf(
            "The file is successfully opened! The number of opened file is "
            "%d\n",
            fo);

        //写入数据，要说明写入数据的字节数
        write(fo, "write into this file", 21);

        // close():成功返回0，失败返回-1
        int fc = close(fo);
        if (fc != -1) {
            printf("The file is successfully closed\n");
        } else {
            printf("The file can't be closed\n");
            return -1;
        }
    } else {
        return -1;
    }
    if (fo = open("./data.txt", O_RDWR)) {
        //从文件读出数据,注意无法边写边读
        char fr[128] = {0};
        int read_num = read(fo, fr, 21);
        if (read_num != -1) {
            printf("read from file:%s %d\n", fr, read_num);
        } else {
            printf("failed to read this file\n");
        }
        close(fo);
    } else {
        return -1;
    }

    return 0;
}
