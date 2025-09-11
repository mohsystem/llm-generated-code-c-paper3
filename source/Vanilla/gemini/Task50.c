#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

char* uploadFile(const char* filePath, const char* serverAddress, int serverPort) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char* response = malloc(1024 * sizeof(char));

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        strcpy(response, "Socket creation error");
        return response;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);

    if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr)<=0) {
        strcpy(response, "Invalid address/ Address not supported");
        return response;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        strcpy(response, "Connection Failed");
        return response;
    }


    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        strcpy(response, "File not found.");
        return response;
    }


    char filename[256];
    strcpy(filename, strrchr(filePath, '/') ? strrchr(filePath, '/') + 1 : filePath);

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);


    send(sock, filename, strlen(filename), 0);
    send(sock , "\n", 1, 0);
    char fileSizeStr[20];
    sprintf(fileSizeStr, "%ld", fileSize);
    send(sock, fileSizeStr, strlen(fileSizeStr), 0);
    send(sock , "\n", 1, 0);

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(sock, buffer, bytesRead, 0);
    }
    fclose(file);
    read(sock , response, 1024);
    close(sock);
    return response;
}

int main() {
    char* serverAddress = "localhost";
    int serverPort = 5000;

    printf("%s\n", uploadFile("test1.txt", serverAddress, serverPort));
    printf("%s\n", uploadFile("test2.pdf", serverAddress, serverPort));
    printf("%s\n", uploadFile("nonexistent.txt", serverAddress, serverPort));
    printf("%s\n", uploadFile("test3.jpg", serverAddress, serverPort));
    printf("%s\n", uploadFile("test4.zip", serverAddress, serverPort));
    
    return 0;
}