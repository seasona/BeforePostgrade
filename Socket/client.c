// 希望通过wifi在手机和电脑之间传输图片
// 理论的平台是安卓和win端，但这两个我暂时都不会
// 所以先将范围缩小到两台linux环境的电脑使用socket传输图片

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER 1024

void errorDie(const char *sc) {
    perror(sc);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("The argument isn't enough.\n");
        exit(1);
    }

    char buffer[MAX_BUFFER];
    int socket_fd;

    char name[100];
    char path[100];

    // 使用TCP传输，UDP压根就不支持listen
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        errorDie("socket");
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    // inet_addr可以将字符串转成ip数字
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(socket_fd, (struct sockaddr *)&server_address,
                sizeof(server_address)) == -1) {
        errorDie("connect");
    }
    printf("The picture's name is: ");
    scanf("%s", name);
    sprintf(path, "./%s", name);
    FILE *pic_stream = fopen(path, "r");
    if (pic_stream == NULL) {
        errorDie("fopen");
    }

    int name_size = strlen(name) + 1;
    send(socket_fd, &name_size, sizeof(name_size), 0);
    send(socket_fd, name, name_size * sizeof(char), 0);

    memset(buffer, 0, sizeof(buffer));
    while (!feof(pic_stream)) {
        fread(buffer, 1, sizeof(buffer), pic_stream);
        send(socket_fd, buffer, sizeof(buffer), 0);
    }

    fclose(pic_stream);
    close(socket_fd);

    return 0;
}
