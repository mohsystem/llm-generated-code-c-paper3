#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void resolveDNS(char* data, int length, char* response) {
    // Simulated DNS resolution
    strcpy(response, "DNS response");
}

int main() {
    int sockfd, port = 53;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Bind the socket to the port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    while (true) {
        // Receive data
        int bytesReceived = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &len);
        if (bytesReceived < 0) {
            perror("Error receiving data");
            continue;
        }

        // Parse and resolve DNS request (simulated)
        resolveDNS(buffer, bytesReceived, response);

        // Send response back
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, len);
    }

    return 0;
}