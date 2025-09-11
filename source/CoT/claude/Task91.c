
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 512
#define MAX_DNS_RECORDS 10

struct DNSRecord {
    char domain[256];
    char ip[16];
};

struct DNSServer {
    int sockfd;
    struct DNSRecord records[MAX_DNS_RECORDS];
    int recordCount;
};

void initDNSServer(struct DNSServer* server) {
    server->recordCount = 2;
    strcpy(server->records[0].domain, "example.com");
    strcpy(server->records[0].ip, "192.168.1.1");
    strcpy(server->records[1].domain, "test.com");
    strcpy(server->records[1].ip, "192.168.1.2");
}

const char* resolveDNS(struct DNSServer* server, const char* domain) {
    for (int i = 0; i < server->recordCount; i++) {
        if (strcmp(server->records[i].domain, domain) == 0) {
            return server->records[i].ip;
        }
    }
    return "Not found";
}

int createUDPServer(const char* ip, int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

void startServer(struct DNSServer* server, const char* ip, int port) {
    server->sockfd = createUDPServer(ip, port);
    if (server->sockfd < 0) {
        return;
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t n = recvfrom(server->sockfd, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr*)&clientAddr, &len);

        if (n > 0) {
            buffer[n] = '\\0';
            const char* response = resolveDNS(server, buffer);
            sendto(server->sockfd, response, strlen(response), 0,
                  (struct sockaddr*)&clientAddr, len);
        }
    }

    close(server->sockfd);
}

int main() {
    struct DNSServer server;
    initDNSServer(&server);

    startServer(&server, "127.0.0.1", 53);

    return 0;
}
