#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    char buffer[1024];
    while (true) {
        int bytesRead = recv(clientSocket, buffer, 1024, 0);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        printf("Client: %s\n", buffer);
        send(clientSocket, buffer, bytesRead, 0);
    }
    close(clientSocket);
    return NULL;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    listen(serverSocket, 3);
    printf("Server started. Listening for incoming connections...\n");

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
        printf("New client connected\n");

        int* clientSocketPtr = malloc(sizeof(int));
        *clientSocketPtr = clientSocket;
        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, clientSocketPtr);
    }

    return 0;
}