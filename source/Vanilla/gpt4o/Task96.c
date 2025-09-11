#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

void *echoClient(void *clientSocket) {
    int socket = *(int *)clientSocket;
    free(clientSocket);
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = read(socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesReceived] = '\0';
        printf("Received: %s\n", buffer);
        send(socket, buffer, bytesReceived, 0);
    }
    close(socket);
    return NULL;
}

int main() {
    int serverSocket, *clientSocket;
    struct sockaddr_in serverAddr;
    int port = 12345;
    pthread_t thread_id;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    printf("Server is listening on port %d\n", port);

    for (int i = 0; i < 5; i++) {
        clientSocket = malloc(sizeof(int));
        *clientSocket = accept(serverSocket, NULL, NULL);
        pthread_create(&thread_id, NULL, echoClient, clientSocket);
    }

    close(serverSocket);
    return 0;
}