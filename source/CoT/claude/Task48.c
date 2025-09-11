
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

typedef struct {
    int socket;
    char name[32];
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(const char* message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender_socket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket == socket) {
            // Shift remaining clients
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);
    char buffer[BUFFER_SIZE];
    char name[32];
    
    // Get client name
    send(client_socket, "Enter your name: ", 16, 0);
    int bytes_received = recv(client_socket, name, sizeof(name) - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return NULL;
    }
    name[bytes_received] = '\\0';
    
    // Add client to list
    pthread_mutex_lock(&clients_mutex);
    if (client_count < MAX_CLIENTS) {
        clients[client_count].socket = client_socket;
        strncpy(clients[client_count].name, name, sizeof(clients[client_count].name) - 1);
        client_count++;
    }
    pthread_mutex_unlock(&clients_mutex);
    
    // Announce new user
    sprintf(buffer, "%s joined the chat!\\n", name);
    broadcast(buffer, client_socket);
    
    // Handle messages
    while (1) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\\0';
        
        char message[BUFFER_SIZE];
        sprintf(message, "%s: %s", name, buffer);
        broadcast(message, client_socket);
    }
    
    // Announce departure
    sprintf(buffer, "%s left the chat!\\n", name);
    broadcast(buffer, client_socket);
    remove_client(client_socket);
    close(client_socket);
    
    return NULL;
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }
    
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(1);
    }
    
    printf("Chat server started on port %d\\n", PORT);
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int* client_socket = malloc(sizeof(int));
        *client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        
        if (*client_socket < 0) {
            free(client_socket);
            continue;
        }
        
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void*)client_socket) != 0) {
            perror("Thread creation failed");
            free(client_socket);
            continue;
        }
        pthread_detach(thread);
    }
    
    close(server_socket);
    return 0;
}
