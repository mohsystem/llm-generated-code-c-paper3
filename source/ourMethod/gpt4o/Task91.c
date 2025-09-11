#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 512

void resolveDns(const char* requestData, char* responseData, size_t dataSize) {
    // Dummy implementation, returns the same data
    memcpy(responseData, requestData, dataSize);
}

void listenAndServe(const char* ipAddress, int port) {
    int sock;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress);
    serverAddr.sin_port = htons(port);

    if (bind(sock, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sock);
        return;
    }

    while (1) {
        ssize_t n = recvfrom(sock, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&clientAddr, &addrLen);
        if (n > 0) {
            resolveDns(buffer, response, n);
            sendto(sock, response, n, MSG_CONFIRM, (const struct sockaddr*)&clientAddr, addrLen);
        }
    }
    close(sock);
}

int main() {
    // Test cases
    listenAndServe("127.0.0.1", 5353);
    return 0;
}