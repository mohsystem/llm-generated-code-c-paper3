
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char* message, int sender) {
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i] != sender) {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i] == socket) {
            for(int j = i; j < client_count-1; j++) {
                clients[j] = clients[j+1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    close(socket);
}

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    char buffer[BUFFER_SIZE];
    
    while(1) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if(bytes_received <= 0) {
            remove_client(client_socket);
            break;
        }
        buffer[bytes_received] = '\\0';
        printf("Received: %s\\n", buffer);
        broadcast(buffer, client_socket);
    }
    return NULL;
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Chat Server started on port 5000\\n");
    
    while(1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if(client_count < MAX_CLIENTS) {
            pthread_mutex_lock(&mutex);
            clients[client_count++] = client_socket;
            pthread_mutex_unlock(&mutex);
            
            pthread_t thread;
            pthread_create(&thread, NULL, handle_client, &client_socket);
            pthread_detach(thread);
        } else {
            char* msg = "Server is full";
            send(client_socket, msg, strlen(msg), 0);
            close(client_socket);
        }
    }
    
    close(server_socket);
    return 0;
}
