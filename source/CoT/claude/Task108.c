
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 1234
#define BUFFER_SIZE 1024

struct RemoteOperations {
    int (*add)(int a, int b);
    int (*subtract)(int a, int b);
    const char* (*getServerMessage)();
};

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

const char* getServerMessage() {
    return "Hello from server!";
}

void handleClient(int client_socket, struct RemoteOperations* ops) {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int read_size = read(client_socket, buffer, BUFFER_SIZE);
        
        if (read_size <= 0) break;
        
        char response[BUFFER_SIZE];
        if (strncmp(buffer, "add", 3) == 0) {
            int result = ops->add(5, 3); // Example values
            sprintf(response, "%d\\n", result);
        }
        else if (strncmp(buffer, "subtract", 8) == 0) {
            int result = ops->subtract(10, 4); // Example values
            sprintf(response, "%d\\n", result);
        }
        else if (strncmp(buffer, "message", 7) == 0) {
            sprintf(response, "%s\\n", ops->getServerMessage());
        }
        
        write(client_socket, response, strlen(response));
    }
    
    close(client_socket);
}

int main() {
    struct RemoteOperations ops = {
        .add = add,
        .subtract = subtract,
        .getServerMessage = getServerMessage
    };
    
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server started on port %d\\n", PORT);
    
    // Test cases
    printf("Test 1: 5 + 3 = %d\\n", ops.add(5, 3));
    printf("Test 2: 10 - 4 = %d\\n", ops.subtract(10, 4));
    printf("Test 3: -5 + (-3) = %d\\n", ops.add(-5, -3));
    printf("Test 4: 5 - 10 = %d\\n", ops.subtract(5, 10));
    printf("Test 5: %s\\n", ops.getServerMessage());
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        
        handleClient(client_socket, &ops);
    }
    
    close(server_socket);
    return 0;
}
