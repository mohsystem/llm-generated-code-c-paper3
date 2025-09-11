#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUF_SIZE 1024

int client_count = 0;
int client_sockets[10];
pthread_mutex_t mutex;

void* client_handler(void* arg) {
    int client_socket = *((int*)arg);
    char message[BUF_SIZE];
    int str_len;

    while ((str_len = read(client_socket, message, sizeof(message) - 1)) != 0) {
        message[str_len] = '\0';
        printf("Received: %s\n", message);
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < client_count; i++) {
            if (client_sockets[i] != client_socket) {
                write(client_sockets[i], message, str_len);
            }
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < client_count; i++) {
        if (client_sockets[i] == client_socket) {
            while (i++ < client_count - 1) {
                client_sockets[i] = client_sockets[i + 1];
            }
            break;
        }
    }
    client_count--;
    pthread_mutex_unlock(&mutex);
    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    pthread_t thread;

    pthread_mutex_init(&mutex, NULL);

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket() error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() error");
        exit(1);
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen() error");
        exit(1);
    }

    printf("Server started...\n");
    while (1) {
        client_addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == -1) {
            perror("accept() error");
            continue;
        }

        pthread_mutex_lock(&mutex);
        client_sockets[client_count++] = client_socket;
        pthread_mutex_unlock(&mutex);

        pthread_create(&thread, NULL, client_handler, (void*)&client_socket);
        pthread_detach(thread);
    }

    close(server_socket);
    pthread_mutex_destroy(&mutex);
    return 0;
}