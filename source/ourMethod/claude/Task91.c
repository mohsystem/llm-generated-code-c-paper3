
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define BUFFER_SIZE 512
#define DNS_HEADER_LENGTH 12

void start_dns_server(const char* ip_address, int port) {
    int sock;
    struct sockaddr_in server_addr;
    uint8_t buffer[BUFFER_SIZE];
    
    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Socket creation failed: %s\\n", strerror(errno));
        return;
    }
    
    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet', type='text')