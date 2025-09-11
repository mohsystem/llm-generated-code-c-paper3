
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024
#define PORT 12345

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int client_count = 0;

void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; i++) {
        if(clients[i]->socket != sender_socket) {
            if(send(clients[i]->socket, message, strlen(message), 0) < 0) {
                perror("Send failed");
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    client_t *client = (client_t *)arg;
    char buffer[BUFFER_SIZE];

    while(1) {
        int read_len = recv(client->socket, buffer, BUFFER_SIZE, 0);
        if(read_len <= 0) {
            pthread_mutex_lock(&clients_mutex);
            for(int i = 0; i < client_count; i++) {
                if(clients[i]->socket == client->socket) {
                    while(i < client_count-1) {
                        clients[i] = clients[i+1];
                        i++;
                    }
                    break;
                }
            }
            client_count--;
            pthread_mutex_unlock(&clients_mutex);
            break;
        }
        buffer[read_len] = '\\0';
        broadcast_message(buffer, client->socket);
    }

    close(client->socket);
    free(client);
    return NULL;
}

void start_server() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_socket, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Chat Server is running...\\n");

    while(1) {
        client_t *client = malloc(sizeof(client_t));
        socklen_t client_size = sizeof(client->address);
        
        client->socket = accept(server_socket, (struct sockaddr *)&client->address, &client_size);
        if(client->socket < 0) {
            free(client);
            continue;
        }

        pthread_mutex_lock(&clients_mutex);
        if(client_count >= MAX_CLIENTS) {
            pthread_mutex_unlock(&clients_mutex);
            close(client->socket);
            free(client);
            continue;
        }
        clients[client_count++] = client;
        pthread_mutex_unlock(&clients_mutex);

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, (void *)client);
        pthread_detach(thread);
    }
}

void start_client() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[BUFFER_SIZE];
    while(1) {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);
        if(send(sock, message, strlen(message), 0) < 0) {
            perror("Send failed");
            break;
        }
    }
    close(sock);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s [-s|-c]\\n", argv[0]);
        printf("-s: start server\\n");
        printf("-c: start client\\n");
        return 1;
    }

    if(strcmp(argv[1], "-s") == 0) {
        start_server();
    } else if(strcmp(argv[1], "-c") == 0) {
        start_client();
    } else {
        printf("Invalid argument\\n");
        return 1;
    }

    return 0;
}
