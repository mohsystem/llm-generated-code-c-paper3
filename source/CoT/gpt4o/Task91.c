#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

struct DNSRecord {
    char domain[256];
    char ip[16];
};

struct DNSRecord dnsRecords[] = {
    {"example.com", "93.184.216.34"},
    {"google.com", "142.250.190.14"},
    {"localhost", "127.0.0.1"}
};

const char* resolveDNS(const char* domain) {
    for (int i = 0; i < sizeof(dnsRecords) / sizeof(dnsRecords[0]); ++i) {
        if (strcmp(dnsRecords[i].domain, domain) == 0) {
            return dnsRecords[i].ip;
        }
    }
    return "0.0.0.0";
}

void listenAndServeDNS(const char* ip, int port) {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[512];
    socklen_t addrLen = sizeof(clientAddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serverAddr.sin_addr);

    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &addrLen);
        buffer[n] = '\0';
        const char* resolvedIP = resolveDNS(buffer);
        sendto(sockfd, resolvedIP, strlen(resolvedIP), 0, (const struct sockaddr *)&clientAddr, addrLen);
    }
}

int main() {
    listenAndServeDNS("127.0.0.1", 5353);
    return 0;
}