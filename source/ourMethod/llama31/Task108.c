#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_received < 0) {
        perror("Error reading from client");
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received object: %s\n", buffer);

    // Manipulate the object
    if (strlen(buffer) > 0) {
        for (int i = 0; i < strlen(buffer); i++) {
            buffer[i] = toupper(buffer[i]);
        }
        send(client_socket, buffer, strlen(buffer), 0);
    } else {
        send(client_socket, "Unsupported object type", 24, 0);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    listen(server_socket, 1);
    printf("Server started on port 8000. Waiting for client connections...\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
        if (client_socket < 0) {
            perror("Error accepting client connection");
            continue;
        }

        printf("Client connected\n");
        handle_client(client_socket);
        close(client_socket);
    }

    return 0;
}