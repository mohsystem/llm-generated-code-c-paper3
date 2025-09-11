#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void run_server(int socket, struct sockaddr_in client_addr, socklen_t client_len) {
    char buffer[1024];

    while (true) {
        int bytes_received = recvfrom(socket, buffer, 1024, 0, (struct sockaddr*)&client_addr, &client_len);
        if (bytes_received < 0) {
            perror("Failed to receive data");
            continue;
        }

        // Parse the DNS request
        // Simulate DNS resolution (in real scenario, you would query a DNS server)
        char response[1024];
        sprintf(response, "DNS response for %s", buffer);

        // Send the response back
        sendto(socket, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
    }
}

int main() {
    int socket_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_fd < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(53);

    // Bind socket
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    run_server(socket_fd, client_addr, client_len);

    return 0;
}