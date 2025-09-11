
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <ctype.h>

#define PORT 8080
#define MAX_CLIENTS 50
#define BUFFER_SIZE 1024
#define MAX_MESSAGE_SIZE 1000

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_t;

typedef struct {
    client_t* clients[MAX_CLIENTS];
    int count;
    pthread_mutex_t mutex;
} client_pool_t;

static client_pool_t client_pool = {
    .count = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER
};

static volatile bool running = true;

void signal_handler(int signum) {
    running = false;
}

char* sanitize_message(const char* message) {
    if (!message) return NULL;
    
    size_t len = strlen(message);
    char* sanitized = (char*)malloc(len + 1);
    if (!sanitized) return NULL;
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isprint(message[i]) && message[i] != '<' && message[i] != '>' && 
            message[i] != '"' && message[i] != '\\'') {
            sanitized[j++] = message[i];
        }
    }
    sanitized[j] = '\\0';
    return sanitized;
}

void broadcast_message(const char* message, int sender_socket) {
    pthread_mutex_lock(&client_pool.mutex);
    
    for (int i = 0; i < client_pool.count; i++) {
        if (client_pool.clients[i] && client_pool.clients[i]->socket != sender_socket) {
            send(client_pool.', type='text')