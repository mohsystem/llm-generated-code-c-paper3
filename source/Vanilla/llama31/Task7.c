#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

// Server side
typedef struct {
    int clientSocket;
} ClientData;

void* handleClient(void* data) {
    ClientData* clientData = (ClientData*)data;
    char buffer[BUFFER_SIZE];
    read(clientData->clientSocket, buffer, BUFFER_SIZE);
    char* username = strtok(buffer, ",");
    char* password = strtok(NULL, ",");

    if (strcmp(username, "user1") == 0 && strcmp(password, "password1") == 0 ||
        strcmp(username, "user2") == 0 && strcmp(password, "password2") == 0) {
        write(clientData->clientSocket, "Login successful", 15);
        while (true) {
            read(clientData->clientSocket, buffer, BUFFER_SIZE);
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
            printf("Client: %s\n", buffer);
            write(clientData->clientSocket, "Server: Message received", 24);
        }
    } else {
        write(clientData->clientSocket, "Invalid credentials", 20);
    }
    close(clientData->clientSocket);
    free(clientData);
    return NULL;
}

void startServer(int port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    listen(serverSocket, 3);

    printf("Server started. Waiting for clients...\n");
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("Error accepting client");
            continue;
        }
        printf("Client connected\n");

        ClientData* clientData = malloc(sizeof(ClientData));
        clientData->clientSocket = clientSocket;
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, handleClient, clientData);
        pthread_detach(clientThread);
    }
}

int main() {
    startServer(8000);
    return 0;
}