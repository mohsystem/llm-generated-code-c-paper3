
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

#define BUFFER_SIZE 512

void parse_domain_name(const unsigned char* data, char* domain) {
    int position = 12; // Skip DNS header
    int domain_pos = 0;
    
    while (data[position] != 0) {
        int length = data[position];
        position++;
        
        for (int i = 0; i < length; i++) {
            domain[domain_pos++] = (char)data[position + i];
        }
        domain[domain_pos++] = '.';
        position += length;
    }
    
    if (domain_pos > 0) {
        domain[domain_pos - 1] = '\\0'; // Remove trailing dot
    } else {
        domain[0] = '\\0';
    }
}

void create_dns_response(unsigned char* response, uint16_t query_id, const char* domain) {
    // DNS Header
    response[0] = (query_id >> 8) & 0xFF;
    response[1] = query_id & 0xFF;
    response[2] = 0x81; // Response + Recursion
    response[3] = 0x80;
    response[7] = 0x01; // 1 answer
    
    // Question pointer
    response[12] = 0xC0;
    response[13] = 0x0C;
    
    // Answer
    response[14] = 0x00;
    response[15] = 0x01; // Type A
    response[16] = 0x00;
    response[17] = 0x01; // Class IN
    response[21] = 0x00; // TTL
    response[22] = 0x04; // Data length
    
    // Mock IP address (127.0.0.1)
    response[23] = 127;
    response[24] = 0;
    response[25] = 0;
    response[26] = 1;
}

void start_dns_server(const char* ip_address, int port) {
    #ifdef _WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        printf("Socket creation failed\\n");
        return;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_address);
    
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind failed\\n");
        return;
    }
    
    unsigned char buffer[BUFFER_SIZE];
    unsigned char response[BUFFER_SIZE];
    char domain[256];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    while (1) {
        int n = recvfrom(sock, (char*)buffer, BUFFER_SIZE, 0,
                       (struct sockaddr*)&client_addr, &client_len);
        
        if (n > 0) {
            uint16_t query_id = (buffer[0] << 8) | buffer[1];
            parse_domain_name(buffer, domain);
            
            memset(response, 0, BUFFER_SIZE);
            create_dns_response(response, query_id, domain);
            
            sendto(sock, (char*)response, 32, 0,
                  (struct sockaddr*)&client_addr, client_len);
        }
    }
    
    #ifdef _WIN32
        closesocket(sock);
        WSACleanup();
    #else
        close(sock);
    #endif
}

int main() {
    // Test case 1: Start server on localhost:53
    start_dns_server("127.0.0.1",', type='text')