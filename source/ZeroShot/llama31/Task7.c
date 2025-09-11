#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

// Server side
typedef struct {
    int socket;
} client_args;

void* handleClient(void* args) {
    client_args* client = (client_args*)args;
    char buffer[1024] = {0};
    read(client->socket, buffer, 1024);
    char* command = strtok(buffer, " ");
    if (strcmp(command, "LOGIN") == 0) {
        char* username = strtok(NULL, " ");
        char* password = strtok(NULL, " ");
        // Simulate loading users from a file
        if (strcmp(username, "user1") == 0 && strcmp(password, "password1") == 0) {
            send(client->socket, "LOGIN_SUCCESS", 13, 0);
        } else if (strcmp(username, "user2") == 0 && strcmp(password, "password2") == 0) {
            send(client->socket, "LOGIN_SUCCESS", 13, 0);
        } else {
            send(client->socket, "LOGIN_FAILURE", 14, 0);
        }
    }
    close(client->socket);
    free(args);
    return NULL;
}

void startServer(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for clients...\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");

        client_args* client = malloc(sizeof(client_args));
        client->socket = new_socket;
        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handleClient, client);
        pthread_detach(client_thread);
    }
}

// Client side
void login(int sock, const char* username, const char* password) {
    char request[1024];
    sprintf(request, "LOGIN %s %s", username, password);
    send(sock, request, strlen(request), 0);
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    printf("%s\n", buffer);
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, (void* (*)(void*))startServer, (void*)8000);
    pthread_detach(server_thread);

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    login(sock, "user1", "password1");
    login(sock, "user2", "wrongpassword");

    return 0;
}