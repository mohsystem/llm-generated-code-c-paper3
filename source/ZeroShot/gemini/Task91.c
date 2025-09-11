#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// ... (same helper functions: extract_domain_name, mock_resolve, create_dns_response as in C++ code)

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9876);
    server_addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    socklen_t client_len = sizeof(client_addr);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len);
        if (n < 0) {
            perror("Error receiving data");
            continue;
        }

        char domain_name[1024]; // Adjust size as needed
        strncpy(domain_name, extract_domain_name(buffer, n).c_str(), sizeof(domain_name) - 1);
        domain_name[sizeof(domain_name) - 1] = '\0'; // Ensure null termination

        printf("Received request for: %s\n", domain_name);

        char resolved_ip[INET_ADDRSTRLEN]; // To store resolved IP address string
        strncpy(resolved_ip, mock_resolve(domain_name).c_str(), sizeof(resolved_ip) - 1);
        resolved_ip[sizeof(resolved_ip) - 1] = '\0';

        char response[1024];
        snprintf(response, sizeof(response), "IP: %s", resolved_ip);


        sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
        printf("Sent response to: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    close(sockfd);
    return 0;
}