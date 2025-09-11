#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct {
    char key[256];
    char value[256];
} KeyValuePair;

typedef struct {
    KeyValuePair *dataStore;
    int size;
    pthread_mutex_t lock;
} Task108;

void init(Task108 *server) {
    server->dataStore = NULL;
    server->size = 0;
    pthread_mutex_init(&server->lock, NULL);
}

void put(Task108 *server, const char *key, const char *value) {
    pthread_mutex_lock(&server->lock);
    for (int i = 0; i < server->size; i++) {
        if (strcmp(server->dataStore[i].key, key) == 0) {
            strcpy(server->dataStore[i].value, value);
            pthread_mutex_unlock(&server->lock);
            return;
        }
    }
    server->dataStore = realloc(server->dataStore, sizeof(KeyValuePair) * (server->size + 1));
    strcpy(server->dataStore[server->size].key, key);
    strcpy(server->dataStore[server->size].value, value);
    server->size++;
    pthread_mutex_unlock(&server->lock);
}

const char* get(Task108 *server, const char *key) {
    pthread_mutex_lock(&server->lock);
    for (int i = 0; i < server->size; i++) {
        if (strcmp(server->dataStore[i].key, key) == 0) {
            pthread_mutex_unlock(&server->lock);
            return server->dataStore[i].value;
        }
    }
    pthread_mutex_unlock(&server->lock);
    return "No data";
}

void removeKey(Task108 *server, const char *key) {
    pthread_mutex_lock(&server->lock);
    for (int i = 0; i < server->size; i++) {
        if (strcmp(server->dataStore[i].key, key) == 0) {
            for (int j = i; j < server->size - 1; j++) {
                server->dataStore[j] = server->dataStore[j + 1];
            }
            server->size--;
            server->dataStore = realloc(server->dataStore, sizeof(KeyValuePair) * server->size);
            pthread_mutex_unlock(&server->lock);
            return;
        }
    }
    pthread_mutex_unlock(&server->lock);
}

void* clientHandler(void *arg) {
    int clientSocket = *((int *)arg);
    Task108 *server = (Task108 *)arg;
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);
    char command[256], key[256], value[256];
    sscanf(buffer, "%s %s %s", command, key, value);
    
    if (strcmp(command, "put") == 0) {
        put(server, key, value);
        send(clientSocket, "Stored successfully", 19, 0);
    } else if (strcmp(command, "get") == 0) {
        const char* result = get(server, key);
        send(clientSocket, result, strlen(result), 0);
    } else if (strcmp(command, "remove") == 0) {
        removeKey(server, key);
        send(clientSocket, "Removed successfully", 20, 0);
    } else {
        send(clientSocket, "Invalid command", 15, 0);
    }
    close(clientSocket);
    return NULL;
}

int main() {
    Task108 server;
    init(&server);
    int serverFd, clientSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    bind(serverFd, (struct sockaddr *)&address, sizeof(address));
    listen(serverFd, 3);
    printf("Server started on port 12345\n");

    while (1) {
        clientSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, clientHandler, &clientSocket);
        pthread_detach(clientThread);
    }
    return 0;
}