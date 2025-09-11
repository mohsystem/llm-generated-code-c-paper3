
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
#define PORT 5000

struct client_info {
    int sockfd;
    char name[32];
};

struct client_info *clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int sender_fd) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i]) {
            if(clients[i]->sockfd != sender_fd) {
                if(write(clients[i]->sockfd, message, strlen(message)) < 0) {
                    perror("Write to descriptor failed");
                }
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    struct client_info *client = (struct client_info *)arg;
    char buffer[BUFFER_SIZE];
    char name[32];
    
    // Get client's name\n    if(read(client->sockfd, name, 32) <= 0) {\n        goto cleanup;\n    }\n    strcpy(client->name, name);\n    \n    sprintf(buffer, "%s has joined\\n", client->name);\n    broadcast_message(buffer, client->sockfd);\n    \n    while(1) {\n        int read_len = read(client->sockfd, buffer, BUFFER_SIZE);\n        if(read_len <= 0) {\n            break;\n        }\n        \n        buffer[read_len] = '\\0';
        char message[BUFFER_SIZE + 32];
        sprintf(message, "%s: %s", client->name, buffer);
        broadcast_message(message, client->sockfd);
    }
    
cleanup:
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i] && clients[i]->sockfd == client->sockfd) {
            clients[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    
    sprintf(buffer, "%s has left\\n", client->name);
    broadcast_message(buffer, client->sockfd);
    close(client->sockfd);
    free(client);
    
    return NULL;
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    if(listen(server_sock, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Chat server started on port %d\\n", PORT);
    
    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        
        if(client_sock < 0) {
            perror("Accept failed");
            continue;
        }
        
        struct client_info *client = (struct client_info *)malloc(sizeof(struct client_info));
        client->sockfd = client_sock;
        
        pthread_mutex_lock(&clients_mutex);
        for(int i = 0; i < MAX_CLIENTS; i++) {
            if(!clients[i]) {
                clients[i] = client;
                client_count++;
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);
        
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, (void*)client);
        pthread_detach(tid);
    }
    
    close(server_sock);
    return 0;
}
