#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

struct Client {
    int id;
    struct sockaddr_in address;
    socklen_t addressLen;
    int socket;
};

void* handleClient(void* arg) {
    struct Client* client = (struct Client*)arg;
    char buffer[BUFFER_SIZE];

    while (1) {
        int bytesRead = recvfrom(client->socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client->address, &client->addressLen);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
        printf("Received from client %d: %s\n", client->id, buffer);

        // Broadcast message to all clients
        // For simplicity, this example does not handle multiple clients.
        // In a real application, you would maintain a list of connected clients.
        sendto(client->socket, buffer, bytesRead, 0, (struct sockaddr*)&client->address, client->addressLen);
    }

    return NULL;
}

void server(int port) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct Client clients[10];
    int clientCount = 0;
    pthread_t threads[10];

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", port);

    while (1) {
        char buffer[BUFFER_SIZE];
        socklen_t clientLen = sizeof(struct sockaddr_in);
        int bytesRead = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clients[clientCount].address, &clientLen);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
        printf("Client %d connected: %s\n", clientCount + 1, buffer);

        clients[clientCount].socket = serverSocket;
        clients[clientCount].id = clientCount;
        pthread_create(&threads[clientCount], NULL, handleClient, (void*)&clients[clientCount]);
        clientCount++;
    }

    close(serverSocket);
}

void client(const char* host, int port) {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, host, &serverAddr.sin_addr);

    printf("Connected to server\n");

    char message[BUFFER_SIZE];
    while (1) {
        fgets(message, sizeof(message), stdin);
        sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server|client> <port>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        server(atoi(argv[2]));
    } else if (strcmp(argv[1], "client") == 0) {
        client("localhost", atoi(argv[2]));
    }

    return 0;
}