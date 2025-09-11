// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

void* handleClient(void* arg) {
    int client_fd = *((int*)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    while (true) {
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Client: %s\n", buffer);
        broadcastMessage(buffer, client_fd);
    }

    close(client_fd);
    return NULL;
}

void broadcastMessage(const char* message, int exclude_client_fd) {
    for (int i = 0; i < client_count; ++i) {
        if (i != exclude_client_fd) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
}

int server_fd;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);
int client_count = 0;

struct Client {
    int socket;
};

struct Client clients[10];

int main() {
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set address and port number for the server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening for incoming connections...\n");

    while (true) {
        // Accept an incoming connection
        int* client_fd_ptr = malloc(sizeof(int));
        *client_fd_ptr = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (*client_fd_ptr < 0) {
            perror("accept");
            continue;
        }

        printf("New client connected\n");

        // Handle client in a separate thread
        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, client_fd_ptr);
        clients[client_count].socket = *client_fd_ptr;
        client_count++;
    }

    return 0;
}