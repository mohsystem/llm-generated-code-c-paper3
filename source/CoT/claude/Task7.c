
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#define PORT 5000
#define MAX_USERS 10
#define BUFFER_SIZE 1024

struct UserCredential {
    char username[50];
    char passwordHash[65];
};

struct UserCredential userCredentials[MAX_USERS];
int userCount = 0;

void hash_password(const char* password, char* hash_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_output + (i * 2), "%02x", hash[i]);
    }
    hash_output[64] = 0;
}

void load_credentials() {
    // In real implementation, load from secure file/database
    strcpy(userCredentials[0].username, "user1");
    hash_password("pass1", userCredentials[0].passwordHash);
    
    strcpy(userCredentials[1].username, "user2");
    hash_password("pass2", userCredentials[1].passwordHash);
    
    userCount = 2;
}

int authenticate_user(const char* username, const char* password) {
    char password_hash[65];
    hash_password(password, password_hash);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(userCredentials[i].username, username) == 0) {
            return strcmp(userCredentials[i].passwordHash, password_hash) == 0;
        }
    }
    return 0;
}

void* server_start(void* arg) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    load_credentials();
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //todo error: missing terminating " character
    // 83 | perror("listen faile', type='text')
    // if (listen(server_fd, 3) < 0) {
    //     perror("listen faile', type='text')
}