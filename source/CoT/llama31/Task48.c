#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_MESSAGE_SIZE 1024

typedef struct {
    int socket;
    struct sockaddr_in address;
} Client;

Client clients[10];
int clientCount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* handleClient(void* arg) {
    int id = *((int*)arg);
    char buffer[MAX_MESSAGE_SIZE];
    ssize_t bytesRead;

    while (1) {
        bytesRead = recvfrom(clients[id].socket, buffer, sizeof(buffer), 0, NULL, NULL);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Client %d: %s", id + 1, buffer);

        pthread_mutex_lock(&mutex);
        for (int i = 0; i < clientCount; ++i) {
            if (i != id) {
                sendto(clients[i].socket, buffer, bytesRead, 0, (struct sockaddr*)&clients[i].address, sizeof(clients[i].address));
            }
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void startServer(int port) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        char buffer[MAX_MESSAGE_SIZE];
        ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientLen);

        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
        printf("Client %d connected: %s", clientCount + 1, buffer);

        clients[clientCount].socket = serverSocket;
        clients[clientCount].address = clientAddr;
        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, (void*)&clientCount);
        clientCount++;
    }

    close(serverSocket);
}

void startClient(const char* host, int port) {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, host, &serverAddr.sin_addr);

    pthread_t receiveThread;
    pthread_create(&receiveThread, NULL, (void* (*)(void*))&receiveMessages, (void*)&clientSocket);

    while (1) {
        char message[MAX_MESSAGE_SIZE];
        fgets(message, sizeof(message), stdin);
        sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    close(clientSocket);
}

void* receiveMessages(void* arg) {
    int clientSocket = *((int*)arg);
    struct sockaddr_in serverAddr;
    socklen_t serverLen = sizeof(serverAddr);
    char buffer[MAX_MESSAGE_SIZE];

    while (1) {
        ssize_t bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &serverLen);
        if (bytesRead == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
        printf("Server: %s", buffer);
    }

    return NULL;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        startServer(8000);
    } else if (strcmp(argv[1], "client") == 0) {
        startClient("localhost", 8000);
    }
    return 0;
}