#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1024

void makeHttpRequest(const char *url) {
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    char *message, *response;
    message = "GET / HTTP/1.1\r\nHost: ";
    strcat(message, url);
    strcat(message, "\r\n\r\n");

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Send request
    send(sockfd, message, strlen(message), 0);

    // Receive response
    response = (char *)malloc(MAXLINE * sizeof(char));
    recv(sockfd, response, MAXLINE, 0);
    printf("Response: %s\n", response);

    free(response);
    close(sockfd);
}

int main() {
    char *urls[] = {
        "http://example.com",
        "http://www.google.com",
        "http://www.apache.org",
        "http://www.python.org",
        "http://www.github.com"
    };

    for (int i = 0; i < 5; ++i) {
        printf("Making request to: %s\n", urls[i]);
        makeHttpRequest(urls[i]);
    }

    return 0;
}