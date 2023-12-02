#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        perror("Error in binding");
        exit(1);
    }

    listen(sockfd, 10);

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    // Server's main loop
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(new_sock, buffer, BUFFER_SIZE, 0);
        if (strcmp(buffer, "exit") == 0) {
            printf("Connection closed by client\n");
            break;
        }
        printf("Client: %s\n", buffer);

        send(new_sock, "ACK", sizeof("ACK"), 0);
    }

    close(new_sock);
    close(sockfd);
    return 0;
}

