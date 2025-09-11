
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex.h>
#include <errno.h>

#define MAX_BUFFER 1024
#define PORT 8888
#define MAX_CLIENTS 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_t;

int validate_input(const char* id, const char* operation) {
    if (!id || !operation || strlen(id) == 0 || strlen(operation) == 0) {
        return 0;
    }
    
    regex_t regex;
    int ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, operation, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

void process_request(int client_socket, const char* id, const char* operation) {
    char response[MAX_BUFFER];
    pthread_mutex_lock(&lock);
    
    if (!validate_input(id, operation)) {
        snprintf(response, sizeof(response), "Invalid input\\n");
    } else {
        snprintf(response, sizeof(response), "Processed: %s with %s\\n", id, operation);
    }
    
    pthread_mutex_unlock(&lock);
    
    send(client_socket, response, strlen(response), 0);
}

void* handle_client(void* arg) {
    client_t* client = (client_t*)arg;
    char buffer[MAX_BUFFER];
    
    while (1) {
        memset(buffer, 0, MAX_BUFFER);
        ssize_t bytes_received = recv(client->socket, buffer, MAX_BUFFER-1, 0);
        
        if (bytes_received <= 0) {
            break;
        }
        
        char* id = strtok(buffer, ":");
        char* operation = strtok(NULL, "\\n");
        
        if (!id || !operation) {
            const char* error = "Invalid request format\\n";
            send(client->socket, error, strlen(error), 0);
            continue;
        }
        
        process_request(client->socket, id, operation);
    }
    
    close(client->socket);
    free(client);
    return NULL;
}

void run_tests() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return;
    }
    
    // Test 1: Valid request
    char response[MAX_BUFFER];
    send(sock, "obj1:read\\n", 10, 0);
    recv(sock, response, MAX_BUFFER-1, 0);
    printf("Test 1', type='text')