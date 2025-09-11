#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
        return 1;
    }

    int portNumber = atoi(argv[1]);
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Could not create socket");
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(serverSocket, 1);
    printf("Server is listening on port %d\n", portNumber);

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected\n");

        char buffer[1024] = {0};
        ssize_t valread;
        while ((valread = read(clientSocket, buffer, 1024)) > 0) {
            printf("Received: %s\n", buffer);
            send(clientSocket, buffer, valread, 0);
            memset(buffer, 0, sizeof(buffer));
        }

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}