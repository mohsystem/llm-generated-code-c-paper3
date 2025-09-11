
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define MAX_CREDENTIALS 100

typedef struct {
    char username[50];
    char password[50];
} Credential;

typedef struct {
    Credential credentials[MAX_CREDENTIALS];
    int count;
} CredentialStore;

CredentialStore store = {0};

void load_credentials() {
    FILE* file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error opening credentials file\\n");
        return;
    }
    
    char line[100];
    while (fgets(line, sizeof(line), file) && store.count < MAX_CREDENTIALS) {
        char* username = strtok(line, ":");
        char* password = strtok(NULL, "\\n");
        
        if (username && password) {
            strncpy(store.credentials[store.count].username, username, sizeof(store.credentials[store.count].username) - 1);
            strncpy(store.credentials[store.count].password, password, sizeof(store.credentials[store.count].password) - 1);
            store.count++;
        }
    }
    
    fclose(file);
}

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < store.count; i++) {
        if (strcmp(store.credentials[i].username, username) == 0 &&
            strcmp(store.credentials[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void* handle_client(void* socket_desc) {
    int sock = *(int*)socket_desc;
    char buffer[BUFFER_SIZE] = {0};
    free(socket_desc);
    
    if', type='text')