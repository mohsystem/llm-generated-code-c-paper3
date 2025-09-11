
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define PORT 12345

typedef struct {
    int socket;
    char name[32];
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(const char* message, int sender) {
    pthread_mutex_lock(&clients_mutex);
    
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    
    int i;
    for (i = 0; i < client_count; i++) {
        if (clients[i].socket == socket) {
            break;
        }
    }
    
    if (i < client_count) {
        for (; i < client_count - 1; i++) {
            clients[i] = clients[i + 1];
        }
        client_count--;
    }
    
    pthread_mutex_unlock(&clients_mutex);
}

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);
    
    char buffer[BUFFER_SIZE];
    char name[32];
    
    // Get client name
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return NULL;
    }
    buffer[bytes_received] = '\\0';
    strncpy(name, buffer, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\\0';
    
    pthread_mutex_lock(&clients_mutex);
    if (client_count < MAX_CLIENTS) {
        clients[client_count].socket = client_socket;
        strncpy(clients[client_count].name, name, sizeof(clients[client_count].name) - 1);
        clients[client_count].name[sizeof(clients[client_count].name) - 1] = '\\0';
        client_count++;
    }
    pthread_mutex_unlock(&clients_mutex);
    
    // Announce new client
    snprintf(buffer, sizeof(buffer), "%s has joined the chat!\\n", name);
    broadcast(buffer, client_socket);
    
    // Handle messages
    while (1) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\\0';
        
        char message[BUFFER_SIZE + 32];
        snprintf(message, sizeof(message), "%s: %s", name, buffer);
        broadcast(message, client_socket);
    }
    
    // Client disconnected
    snprintf(buffer, sizeof(buffer), "%s has left the chat!\\n", name);
    broadcast(buffer, client_socket);
    remove_client(client_socket);
    close(client_socket);
    
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server running on port %d\\n", PORT);
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int* client_socket = malloc(sizeof(int));
        if (client_socket == NULL) {
            perror("Memory allocation failed");
            continue;
        }
        
        *client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (*client_socket < 0) {
            free(client_socket);
            perror("Accept failed");
            continue;
        }
        
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, client_socket) != 0) {
            free(client_socket);
            perror("Thread creation failed");
            continue;
        }
        pthread_detach(thread);
    }
    
    close(server_fd);
    return 0;
}
