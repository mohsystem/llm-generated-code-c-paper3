// code here:
/*
This C implementation provides basic client and server functionality for a chat system login. 
It focuses on demonstrating the core concepts of socket programming and credential checking 
but lacks robust error handling and security measures found in the other language examples.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 5

// Structure to hold client credentials
typedef struct {
    char username[256];
    char password[256];
} Credentials;

// Function to authenticate user credentials (simplified for demonstration)
int authenticate(const Credentials* credentials) {
    // In a real application, this would involve checking against a database or file
    if (strcmp(credentials->username, "user1") == 0 && strcmp(credentials->password, "password123") == 0) {
        return 1; // Authentication successful
    }
    return 0; // Authentication failed
}

// Function to handle client requests
void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    Credentials credentials;

    // Receive credentials from client
    recv(client_socket, &credentials, sizeof(credentials), 0);

    // Authenticate credentials
    if (authenticate(&credentials)) {
        send(client_socket, "LOGIN SUCCESS", 13, 0);
    } else {
        send(client_socket, "LOGIN FAILED", 12, 0);
    }

    close(client_socket);
    free(arg); // Free the dynamically allocated socket
    pthread_exit(NULL);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept incoming connections
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle the client
        pthread_t thread_id;
        int* client_socket_ptr = (int*)malloc(sizeof(int));
        *client_socket_ptr = new_socket;
        pthread_create(&thread_id, NULL, handle_client, (void*)client_socket_ptr);

    }
    return 0;
}