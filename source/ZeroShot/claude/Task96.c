
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void start_server(int port) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return;
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        return;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return;
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return;
    }
    
    printf("Server listening on port %d\\n", port);
    
    while(1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        
        int valread;
        while ((valread = read(client_socket, buffer, 1024)) > 0) {
            send(client_socket, buffer, valread, 0);
            memset(buffer, 0, sizeof(buffer));
        }
        
        close(client_socket);
    }
    
    close(server_fd);
}

int main() {
    // Test cases
    // Note: Only one test case can run at a time since it's a server
    start_server(8080);
    
    // Additional test cases would be:
    // start_server(8081);
    // start_server(8082);
    // start_server(8083);
    // start_server(8084);
    
    return 0;
}
