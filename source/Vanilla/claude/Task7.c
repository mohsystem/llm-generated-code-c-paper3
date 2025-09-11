
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_USERS 3
#define PORT 5000
#define BUFFER_SIZE 1024

// Simple user structure
struct User {
    char username[50];
    char password[50];
};

// Server function
void start_server() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Initialize test users
    struct User users[MAX_USERS] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"user3", "pass3"}
    };
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    printf("Server started on port %d\\n", PORT);
    
    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        read(client_socket, buffer, BUFFER_SIZE);
        
        char *username = strtok(buffer, ":");
        char *password = strtok(NULL, ":");
        
        int authenticated = 0;
        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(users[i].username, username) == 0 && 
                strcmp(users[i].password, password) == 0) {
                authenticated = 1;
                break;
            }
        }
        
        if (authenticated) {
            send(client_socket, "LOGIN_SUCCESS", 12, 0);
        } else {
            send(client_socket, "LOGIN_FAILED", 11, 0);
        }
        
        close(client_socket);
    }
}

// Client function
int login_client(const char* username, const char* password) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    // Create login request
    char request[100];
    sprintf(request, "%s:%s", username, password);
    send(sock, request, strlen(request), 0);
    
    read(sock, buffer, BUFFER_SIZE);
    close(sock);
    
    return strcmp(buffer, "LOGIN_SUCCESS") == 0;
}

int main() {
    // Note: In a real implementation, you would need to use threads or fork
    // to run server and client simultaneously. This is a simplified version
    // that just demonstrates the client functionality.
    
    printf("Test Case 1: %d\\n", login_client("user1", "pass1")); // Should return 1
    printf("Test Case 2: %d\\n", login_client("user2", "pass2")); // Should return 1
    printf("Test Case 3: %d\\n", login_client("user1", "wrongpass")); // Should return 0
    printf("Test Case 4: %d\\n", login_client("nonexistent", "pass")); // Should return 0
    printf("Test Case 5: %d\\n", login_client("user', type='text')