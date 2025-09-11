#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

// Basic DNS query structure (simplified for example)
struct DNSHeader {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

void dns_query_and_response(const char *domain, int record_type);

int main() {
    dns_query_and_response("google.com", 1); // A
    dns_query_and_response("facebook.com", 1); // A
    dns_query_and_response("amazon.com", 1); // A
    dns_query_and_response("wikipedia.org", 1); // A
    dns_query_and_response("example.com", 28); // AAAA
    return 0;
}



void dns_query_and_response(const char *domain, int record_type) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }


    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53);
    inet_pton(AF_INET, "8.8.8.8", &(server_addr.sin_addr));



    // 1. Send DNS query (simplified)
    struct DNSHeader header;
    header.id = htons(12345); // Some random ID
    header.flags = htons(0x0100);  // Recursion desired
    header.qdcount = htons(1);
    header.ancount = 0;
    header.nscount = 0;
    header.arcount = 0;


    char query[1024];
    int query_len = 0;

    memcpy(query + query_len, &header, sizeof(header));
    query_len += sizeof(header);



    // Domain name to DNS format
    char *dom = strdup(domain);
    char *token = strtok(dom, ".");
    while (token != NULL) {
        int len = strlen(token);
        query[query_len++] = len;
        memcpy(query + query_len, token, len);
        query_len += len;
        token = strtok(NULL, ".");
    }
    query[query_len++] = 0;
    free(dom);


    uint16_t qtype = htons(record_type);
    uint16_t qclass = htons(1); // IN
    memcpy(query + query_len, &qtype, sizeof(qtype));
    query_len += sizeof(qtype);
    memcpy(query + query_len, &qclass, sizeof(qclass));
    query_len += sizeof(qclass);


    sendto(sockfd, query, query_len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));


    // 2. Receive response
    socklen_t len = sizeof(server_addr);
    int n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &len);
    if(n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }


    // 3. Parse and print response (simplified)
    struct DNSHeader *response_header = (struct DNSHeader *)buffer;
    uint16_t ancount = ntohs(response_header->ancount);

    if (ancount > 0) {
        printf("DNS Response for %s:\n", domain);
        //  More parsing needed to extract records...
    } else {
        printf("No DNS records found for %s\n", domain);
    }

    close(sockfd);
}