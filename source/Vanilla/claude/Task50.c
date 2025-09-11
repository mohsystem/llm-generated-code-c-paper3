
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

char* uploadFile(const char* filePath, const char* serverAddress, int port) {
    static char result[1024];
    
    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        strcpy(result, "Error: Socket creation failed");
        return result;
    }
    
    // Set server address
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, serverAddress, &server.sin_addr);
    
    // Connect to server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        strcpy(result, "Error: Connection failed");
        return result;
    }
    
    // Open file
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        strcpy(result, "Error: Could not open file");
        return result;
    }
    
    // Get filename from path
    const char* filename = strrchr(filePath, '/');
    if (!filename) filename = strrchr(filePath, '\\\\');\n    if (filename)\n        filename++;\n    else\n        filename = filePath;\n    \n    // Send filename\n    send(sock, filename, strlen(filename), 0);\n    \n    // Send file content\n    char buffer[4096];\n    size_t bytes_read;\n    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {\n        send(sock, buffer, bytes_read, 0);\n    }\n    \n    // Get confirmation\n    int bytes_received = recv(sock, result, sizeof(result) - 1, 0);\n    result[bytes_received] = '\\0';
    
    close(sock);
    fclose(file);
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", uploadFile("test1.txt", "localhost", 8080));
    printf("%s\\n", uploadFile("test2.jpg", "localhost", 8080));
    printf("%s\\n", uploadFile("test3.pdf", "localhost", 8080));
    printf("%s\\n", uploadFile("test4.doc", "localhost", 8080));
    printf("%s\\n", uploadFile("test5.zip", "localhost", 8080));
    return 0;
}
