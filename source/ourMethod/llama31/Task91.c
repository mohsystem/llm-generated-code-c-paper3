#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 53
#define MAXLINE 1024

void parseDNSRequest(char* data, int length, char* domain) {
    // Simplified parsing, in real scenarios use a DNS library
    strncpy(domain, data + 12, length - 12);
    domain[length - 12] = '\0';
}

char* resolveDNS(char* domain) {
    // For simplicity, assume a hardcoded response
    return "192.168.1.1";
}

void createDNSResponse(char* domain, char* ip, char* response) {
    // Simplified response creation, in real scenarios use a DNS library
    strcpy(response, "Hello");
    strcat(response, domain);
    strcat(response, ip);
}

int main() {
    int sockfd, len;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAXLINE];
    char domain[MAXLINE];
    char response[MAXLINE];

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Bind the socket to the specified IP and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    while (true) {
        len = sizeof(cliaddr);
        int n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            continue;
        }

        // Parse DNS request
        parseDNSRequest(buffer, n, domain);

        // Resolve DNS record (for simplicity, assume a hardcoded response)
        char* ip = resolveDNS(domain);

        if (ip != NULL) {
            // Create DNS response
            createDNSResponse(domain, ip, response);

            // Send response back
            sendto(sockfd, response, strlen(response), MSG_CONFIRM, (struct sockaddr*)&cliaddr, len);
        }
    }

    return 0;
}