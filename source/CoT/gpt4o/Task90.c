#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int clients[10];
int clientCount = 0;

void *clientHandler(void *clientSocket) {
    int sock = *(int *)clientSocket;
    char buffer[BUFFER_SIZE];
    int nbytes;

    while ((nbytes = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[nbytes] = '\0';
        printf("Received: %s\n", buffer);

        pthread_mutex_lock(&lock);
        for (int i = 0; i < clientCount; i++) {
            if (clients[i] != sock) {
                write(clients[i], buffer, nbytes);
            }
        }
        pthread_mutex_unlock(&lock);
    }

    close(sock);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < clientCount; i++) {
        if (clients[i] == sock) {
            clients[i] = clients[clientCount - 1];
            clientCount--;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addr_size = sizeof(newAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    printf("Server started on port %d\n", PORT);

    while (1) {
        newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addr_size);
        pthread_mutex_lock(&lock);
        clients[clientCount++] = newSocket;
        pthread_mutex_unlock(&lock);

        pthread_t tid;
        pthread_create(&tid, NULL, clientHandler, &newSocket);
    }

    close(serverSocket);
    return 0;
}