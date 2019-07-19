// 服务器端，可以多次接收，传输了文件名，动态分配端口

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

int main() {
    char name[100];
    char path[100];

    struct sockaddr_in server_address, bind_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = 0;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        errorDie("socket");
    }

    if (bind(server_fd, (struct sockaddr *)&server_address,
             sizeof(server_address)) == -1) {
        errorDie("bind");
    }

    printf("-------------bind success-----------\n");
    socklen_t bind_size = sizeof(bind_address);
    getsockname(server_fd, (struct sockaddr *)&bind_address, &bind_size);
    printf("server address is %d\nserver port is %d\n",
           bind_address.sin_addr.s_addr, ntohs(bind_address.sin_port));

    if (listen(server_fd, 10) == -1) {
        errorDie("listen");
    }

    while (1) {
        struct sockaddr_in client_address;
        socklen_t size = sizeof(client_address);
        int client_fd =
            accept(server_fd, (struct sockaddr *)&client_address, &size);
        if (client_fd == -1) {
            continue;
        }

        int name_size = 0;
        memset(name, 0, sizeof(name));
        memset(path, 0, sizeof(path));

        // 如果socket中没有数据，会在这里卡主
        recv(client_fd, &name_size, sizeof(name_size), 0);
        recv(client_fd, name, name_size * sizeof(char), 0);

        sprintf(path, "./new_%s", name);

        FILE *pic_file = fopen(path, "ab");
        if (pic_file == NULL) {
            errorDie("file");
        }

        char buffer[MAX_BUFFER];
        memset(buffer, 0, sizeof(buffer));
        while (1) {
            int n = recv(client_fd, buffer, sizeof(buffer), 0);
            if (n == 0) {
                break;
            }
            fwrite(buffer, 1, n, pic_file);
        }

        fclose(pic_file);
        close(client_fd);
    }
    close(server_fd);

    return 0;
}