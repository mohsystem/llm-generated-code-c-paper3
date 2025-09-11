#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, 1024, 0);
        if (bytesReceived <= 0) {
            break;
        }
        buffer[bytesReceived] = '\0';
        printf("Client: %s\n", buffer);
        send(clientSocket, ("Server: " + buffer), strlen("Server: ") + bytesReceived, 0);
    }
    close(clientSocket);
    return NULL;
}

void startServer() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    listen(serverSocket, 5);
    printf("Server is listening on port 8000\n");

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            perror("Error accepting client");
            continue;
        }
        printf("New Client Connected\n");
        int* clientSocketPtr = malloc(sizeof(int));
        *clientSocketPtr = clientSocket;
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, handleClient, clientSocketPtr);
        pthread_detach(clientThread);
    }
}

int main() {
    startServer();
    return 0;
}