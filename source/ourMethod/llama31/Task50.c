#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>

void handleFileUpload(int clientSocket) {
    char fileName[1024];
    read(clientSocket, fileName, 1024);
    fileName[1023] = '\0'; // Ensure null-termination

    // Validate file name to prevent path traversal attacks
    if (strchr(fileName, '..') != NULL || strchr(fileName, '/') != NULL) {
        printf("Invalid file name: %s\n", fileName);
        return;
    }

    // Create directory if it does not exist
    char dirPath[] = "uploads";
    DIR* dir = opendir(dirPath);
    if (dir == NULL) {
        mkdir(dirPath, 0777);
    } else {
        closedir(dir);
    }

    char filePath[1024];
    sprintf(filePath, "%s/%s", dirPath, fileName);

    FILE* file = fopen(filePath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return;
    }

    char buffer[1024];
    while (true) {
        ssize_t bytesRead = read(clientSocket, buffer, 1024);
        if (bytesRead <= 0) break;
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(file);
    printf("File uploaded successfully: %s\n", fileName);

    // Send confirmation message back to the client
    char message[] = "File uploaded successfully";
    write(clientSocket, message, strlen(message));

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        fprintf(stderr, "Failed to bind socket\n");
        return 1;
    }

    listen(serverSocket, 5);
    printf("Server started. Listening for incoming connections...\n");

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            fprintf(stderr, "Failed to accept client connection\n");
            continue;
        }

        printf("Incoming connection from %s\n", inet_ntoa(clientAddress.sin_addr));

        // Handle file upload in a separate thread to avoid blocking
        pthread_t thread;
        pthread_create(&thread, NULL, (void* (*)(void*))handleFileUpload, &clientSocket);
    }

    return 0;
}