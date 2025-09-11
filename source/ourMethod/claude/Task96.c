
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char* start_server(int port) {
    static char result[BUFFER_SIZE];
    memset(result, 0, BUFFER_SIZE);
    
    if (port < 0 || port > 65535) {
        snprintf(result, BUFFER_SIZE, "Invalid port number");
        return result;
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        snprintf(result, BUFFER_SIZE, "Failed to create socket");
        return result;
    }

    struct timeval timeout;
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;
    setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(server_socket);
        snprintf(result, BUFFER_SIZE, "Bind failed");
        return result;
    }

    if (listen(server_socket, 1) < 0) {
        close(server_socket);
        snprintf(result, BUFFER_SIZE, "Listen failed");
        return result;
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

    if (client_socket < 0) {
        close(server_socket);
        snprintf(result, BUFFER_SIZE, "Accept failed");
        return result;
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    ssize_t bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0) {
        send(client_socket, buffer, bytes_read, 0);
        snprintf(result, BUFFER_SIZE, "Message echoed: %s", buffer);
    } else {
        snprintf(result, BUFFER_SIZE, "No data received");
    }

    close(client_socket);
    close(server_socket);
    return result;
}

int main() {
    // Test cases
    printf("Test 1: %s\\n", start_server(8080));  // Valid port
    printf("Test 2: %s\\n", start_server(-1));    // Invalid port  
    printf("Test 3: %s\\n", start_server(65536)); // Invalid port
    printf("Test 4: %s\\n", start_server(0));     // System assigned port
    printf("Test 5: %s\\n", start_server(9090));  // Valid port
    return 0;
}
