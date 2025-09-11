
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define BUFFER_SIZE 1024
#define PORT 8000

// Simple user structure
struct User {
    char username[50];
    char password_hash[SHA256_DIGEST_LENGTH*2 + 1];
};

struct User users[MAX_USERS];
int user_count = 0;

// Hash password using SHA-256
void hash_password(const char* password, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH*2] = 0;
}

// Client functions
int client_login(const char* username, const char* password) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation error\\n");
        return -1;
    }
    
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\\n");
        return -1;
    }
    
    char hashed_pass[SHA256_DIGEST_LENGTH*2 + 1];
    hash_password(password, hashed_pass);
    
    char request[BUFFER_SIZE];
    snprintf(request, BUFFER_SIZE, "LOGIN:%s:%s\\n", username, hashed_pass);
    send(sock, request, strlen(request), 0);
    
    char buffer[BUFFER_SIZE] = {0};
    read(sock, buffer, BUFFER_SIZE);
    close(sock);
    
    printf("Server response: %s", buffer);
    return 0;
}

// Server functions
void* handle_client(void* socket_desc) {
    int sock = *(int*)socket_desc;
    char buffer[BUFFER_SIZE] = {0};
    read(sock, buffer, BUFFER_SIZE);
    
    char* command = strtok(buffer, ":");
    char* username = strtok(NULL, ":");
    char* password = strtok(NULL, "\\n");
    
    char response[BUFFER_SIZE];
    if (command && username && password && strcmp(command, "LOGIN") == 0) {
        int i;
        int found = 0;
        for(i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, username) == 0 && 
                strcmp(users[i].password_hash, password) == 0) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            strcpy(response, "Login successful\\n");
        } else {
            strcpy(response, "Invalid credentials\\n");
        }
    } else {
        strcpy(response, "Invalid request\\n");
    }
    
    send(sock, response, strlen(response), 0);
    close(sock);
    free(socket_desc);
    return 0;
}

void start_server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY', type='text')