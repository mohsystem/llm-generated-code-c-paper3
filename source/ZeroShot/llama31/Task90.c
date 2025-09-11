#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    char buffer[256];
    int bytesRead;
    while (true) {
        bytesRead = recv(clientSocket, buffer, 256, 0);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        printf("Client: %s\n", buffer);
        char response[256];
        sprintf(response, "Server: %s", buffer);
        send(clientSocket, response, strlen(response), 0);
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
        perror("Error creating socket");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    listen(serverSocket, 5);
    printf("Server started. Listening for incoming connections...\n");

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("Error accepting connection");
            continue;
        }
        printf("New client connected\n");

        int* clientSocketPtr = malloc(sizeof(int));
        *clientSocketPtr = clientSocket;
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, handleClient, clientSocketPtr);
        pthread_detach(clientThread);
    }

    return 0;
}