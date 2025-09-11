// C code to create a UDP socket for DNS requests
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void listenOnUDPSocket(const char* ipAddress, int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress, &serverAddr.sin_addr);

    bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[512];
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (1) {
        int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        buffer[len] = '\0';
        printf("Received DNS request: %s\n", buffer);

        // Resolve DNS records (stub response for demonstration)
        const char* dnsResponse = "Resolved IP: 127.0.0.1";

        // Send response back
        sendto(sock, dnsResponse, strlen(dnsResponse), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    }

    close(sock);
}

int main() {
    // Test cases
    listenOnUDPSocket("127.0.0.1", 5353);
    return 0;
}