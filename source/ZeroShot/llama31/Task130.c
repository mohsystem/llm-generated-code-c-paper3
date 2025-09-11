// This is a very simplified and incomplete example.
// In real-world scenarios, you would use a library or framework.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Set up server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(sockfd, 3) < 0) {
        perror("listen failed");
        exit(1);
    }

    int clilen = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
    if (connfd < 0) {
        perror("accept failed");
        exit(1);
    }

    // Handle request and send response
    char buffer[1024];
    read(connfd, buffer, 1024);
    char* response = "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: http://www.example.com\r\nAccess-Control-Allow-Methods: *\r\nAccess-Control-Allow-Headers: *\r\nAccess-Control-Allow-Credentials: true\r\n\r\nHello, World!";
    send(connfd, response, strlen(response), 0);

    close(connfd);
    close(sockfd);

    return 0;
}