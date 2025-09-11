
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define PORT 5000

int clients[MAX_CLIENTS];
int n_clients = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char* message, int sender_sd) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < n_clients; i++) {
        if(clients[i] != sender_sd) {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void* handle_client(void* arg) {
    int client_sd = *((int*)arg);
    char buffer[BUFFER_SIZE];
    
    while(1) {
        int bytes_received = recv(client_sd, buffer, BUFFER_SIZE, 0);
        if(bytes_received <= 0) {
            pthread_mutex_lock(&clients_mutex);
            for(int i = 0; i < n_clients; i++) {
                if(clients[i] == client_sd) {
                    while(i < n_clients-1) {
                        clients[i] = clients[i+1];
                        i++;
                    }
                    break;
                }
            }
            n_clients--;
            pthread_mutex_unlock(&clients_mutex);
            close(client_sd);
            return NULL;
        }
        buffer[bytes_received] = '\\0';
        broadcast(buffer, client_sd);
    }
    return NULL;
}

void start_server() {
    int server_sd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(server_sd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sd, 5);
    
    while(1) {
        int client_sd = accept(server_sd, NULL, NULL);
        
        pthread_mutex_lock(&clients_mutex);
        clients[n_clients] = client_sd;
        n_clients++;
        pthread_mutex_unlock(&clients_mutex);
        
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, &client_sd);
        pthread_detach(thread);
    }
}

void connect_client() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Test cases
    char* test_messages[] = {
        "Hello everyone!",
        "How are you doing?",
        "This is a test message",
        "Testing broadcast",
        "Goodbye!"
    };
    
    for(int i = 0; i < 5; i++) {
        send(sock, test_messages[i], strlen(test_messages[i]), 0);
        sleep(1);
    }
    
    close(sock);
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, (void*)start_server, NULL);
    
    sleep(1); // Wait for server to start
    
    connect_client();
    
    pthread_join(server_thread, NULL);
    return 0;
}
