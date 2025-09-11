#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 256

struct Client {
    int socket;
    struct sockaddr_in address;
};

void* handleClient(void* arg) {
    struct Client* client = (struct Client*)arg;
    char buffer[BUFFER_SIZE];
    int bytesRead;

    while (1) {
        bytesRead = recvfrom(client->socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client->address, NULL);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Received from client: %s\n", buffer);

        // Broadcast message to all clients
        // For simplicity, this example does not handle broadcasting
        // In a real application, you would need to maintain a list of clients and send to each one
    }

    return NULL;
}

void startServer(int port) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct Client clients[10];
    int clientCount = 0;
    pthread_t threads[10];

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (1) {
        char buffer[BUFFER_SIZE];
        int bytesRead = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clients[clientCount].address, NULL);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Client %d connected: %s\n", clientCount + 1, buffer);

        // Create a new thread for each client
        clients[clientCount].socket = serverSocket;
        pthread_create(&threads[clientCount], NULL, handleClient, (void*)&clients[clientCount]);
        clientCount++;
    }

    close(serverSocket);
}

int main() {
    startServer(8000);
    return 0;
}