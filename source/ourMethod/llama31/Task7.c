#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Server side
void start_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, 1024);
    char* credentials = strdup(buffer);
    char* colon = strchr(credentials, ':');
    if (colon == NULL) {
        send(new_socket, "Invalid credentials format", 24, 0);
        free(credentials);
        return;
    }

    *colon = '\0';
    char* username = credentials;
    char* password = colon + 1;

    if (authenticate(username, password)) {
        send(new_socket, "Authenticated", 11, 0);
        handle_chat(new_socket);
    } else {
        send(new_socket, "Authentication failed", 20, 0);
    }

    free(credentials);
    close(new_socket);
}

int authenticate(const char* username, const char* password) {
    // Replace with secure authentication logic
    return strcmp(username, "user") == 0 && strcmp(password, "pass") == 0;
}

void handle_chat(int socket) {
    char buffer[1024] = {0};
    while (true) {
        read(socket, buffer, 1024);
        char* message = strdup(buffer);
        if (message == NULL || strcmp(message, "exit") == 0) {
            free(message);
            break;
        }
        printf("Client: %s\n", message);
        send(socket, ("Server: " + message), strlen(message) + 8, 0);
        free(message);
    }
}

int main() {
    start_server(2000);
    return 0;
}