#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345

void* handle_client(void* socket_desc) {
    int sock = *(int*)socket_desc;
    char buffer[1024];
    int read_size;

    while ((read_size = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[read_size] = '\0';
        printf("Received: %s\n", buffer);
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    free(socket_desc);
    return 0;
}

int main() {
    int server_fd, client_sock, *new_sock;
    struct sockaddr_in server, client;
    socklen_t c = sizeof(struct sockaddr_in);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Could not create socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 3);

    while ((client_sock = accept(server_fd, (struct sockaddr*)&client, &c))) {
        pthread_t client_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
        pthread_create(&client_thread, NULL, handle_client, (void*)new_sock);
    }

    if (client_sock < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}