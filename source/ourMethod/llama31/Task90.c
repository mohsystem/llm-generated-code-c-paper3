#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 256

void* handleClient(void* arg) {
    int clientSocket = *(int*)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            break;
        }

        buffer[bytesReceived] = '\0';
        printf("Received message: %s\n", buffer);

        // Simulate broadcasting by sending the message back to the client
        send(clientSocket, buffer, bytesReceived, 0);
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
        perror("Error creating server socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding server socket");
        exit(1);
    }

    if (listen(serverSocket, 5) < 0) {
        perror("Error listening on server socket");
        exit(1);
    }

    printf("Chat server started on port 8000\n");

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("Error accepting client connection");
            continue;
        }

        printf("New client connected\n");

        int* clientSocketPtr = malloc(sizeof(int));
        *clientSocketPtr = clientSocket;

        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, clientSocketPtr);
        pthread_detach(thread);
    }

    return 0;
}