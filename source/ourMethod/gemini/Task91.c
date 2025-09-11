// This implementation in C is complex and requires significant effort to implement securely.
// A basic sketch is provided, but fully implementing DNS parsing and resolution in C is beyond the scope.  
// Recommend using a higher level library if you need production C code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


// ... (Implementation for parse_domain_name and build_dns_response similar to C++ example) ...


void dns_server(const char* ip_address, int port) {
  int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[512];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(sockfd);
        return;
    }


    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        return;
    }

    printf("DNS Server started on %s:%d\n", ip_address, port);
    // ... (Rest of the implementation would be very similar to C++ version.
    //      Error checking and robust DNS parsing/response building are essential)
}



int main() {
    dns_server("127.0.0.1", 5353);
    return 0;
}