
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 2048
#define PORT 12345

struct Client {
    int socket;
    char name[32];
};

struct Client clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i].socket != sender_socket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int socket) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i].socket == socket) {
            for(int j = i; j < client_count-1; j++) {
                clients[j] = clients[j+1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[BUFFER_SIZE];
    char name[32];
    int read_size;
    
    // Receive client's name\n    read_size = recv(client_socket, name, 32, 0);\n    if(read_size > 0) {\n        name[read_size] = '\\0';\n        pthread_mutex_lock(&clients_mutex);\n        for(int i = 0; i < client_count; i++) {\n            if(clients[i].socket == client_socket) {\n                strcpy(clients[i].name, name);\n                break;\n            }\n        }\n        pthread_mutex_unlock(&clients_mutex);\n        \n        char welcome[50];\n        sprintf(welcome, "%s has joined the chat!\\n", name);\n        broadcast_message(welcome, client_socket);\n    }\n    \n    while((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {\n        buffer[read_size] = '\\0';
        char message[BUFFER_SIZE + 32];
        sprintf(message, "%s: %s\\n", name, buffer);
        broadcast_message(message, client_socket);
    }
    
    char goodbye[50];
    sprintf(goodbye, "%s has left the chat!\\n", name);
    broadcast_message(goodbye, client_socket);
    
    remove_client(client_socket);
    close(client_socket);
    free(arg);
    return NULL;
}

int main() {
    int server_socket, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        perror("Socket creation failed");
        return -1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return -1;
    }
    
    if(listen(server_socket, 10) < 0) {
        perror("Listen failed");
        return -1;
    }
    
    printf("Chat server is running...\\n");
    
    while(1) {
        new_sock = malloc(sizeof(int));
        *new_sock = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        
        if(*new_sock < 0) {
            perror("Accept failed");
            free(new_sock);
            continue;
        }
        
        pthread_mutex_lock(&clients_mutex);
        if(client_count >= MAX_CLIENTS) {
            printf("Maximum clients reached. Connection rejected.\\n");
            close(*new_sock);
            free(new_sock);
            pthread_mutex_unlock(&clients_mutex);
            continue;
        }
        
        clients[client_count].socket = *new_sock;
        client_count++;
        pthread_mutex_unlock(&clients_mutex);
        
        pthread_t thread_id;
        if(pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) < 0) {
            perror("Could not create thread");
            remove_client(*new_sock);
            close(*new_sock);
            free(new_sock);
            continue;
        }
        pthread_detach(thread_id);
    }
    
    close(server_socket);
    return 0;
}
