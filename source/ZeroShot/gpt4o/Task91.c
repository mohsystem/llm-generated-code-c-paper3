#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void listenDNS(const char* ip, int port) {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[512];
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serverAddr.sin_addr);
    
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    while (1) {
        int len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        buffer[len] = '\0';
        printf("Received DNS query: %s\n", buffer);
        
        // Simplified DNS response example
        char responseMessage[512];
        snprintf(responseMessage, sizeof(responseMessage), "Response to: %s", buffer);
        sendto(sockfd, responseMessage, strlen(responseMessage), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    }

    close(sockfd);
}

int main() {
    listenDNS("0.0.0.0", 5353);
    return 0;
}