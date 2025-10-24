#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>

/* Security: Validate port range to prevent invalid socket configuration */
int isValidPort(int port) {
    return port > 0 && port <= 65535;
}

/* Security: Safe buffer size with maximum limit to prevent excessive memory usage */
#define MAX_BUFFER_SIZE 65536  /* 64KB limit */
#define INITIAL_BUFFER_SIZE 4096

/* Security: Portable secure memset that won't be optimized away */
void secure_memset(void *ptr, int value, size_t num) {
    if (ptr == NULL || num == 0) {
        return;
    }
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
}

/* Security: Echo server with input validation and bounds checking */
int runEchoServer(int port) {
    int server_fd = -1;
    int client_fd = -1;
    char *buffer = NULL;
    int result = -1;

    /* Security: Validate port parameter */
    if (!isValidPort(port)) {
        fprintf(stderr, "Error: Invalid port number. Must be 1-65535.\n");
        return -1;
    }

    /* Security: Create socket with error checking */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        fprintf(stderr, "Error: Failed to create socket: %s\n", strerror(errno));
        return -1;
    }

    /* Security: Set SO_REUSEADDR to avoid "Address already in use" errors */
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        fprintf(stderr, "Error: setsockopt failed: %s\n", strerror(errno));
        close(server_fd);
        return -1;
    }

    /* Security: Initialize address structure with zeros to prevent info leaks */
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((uint16_t)port);

    /* Security: Bind socket with error checking */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        fprintf(stderr, "Error: Bind failed: %s\n", strerror(errno));
        close(server_fd);
        return -1;
    }

    /* Security: Listen with reasonable backlog */
    if (listen(server_fd, 5) < 0) {
        fprintf(stderr, "Error: Listen failed: %s\n", strerror(errno));
        close(server_fd);
        return -1;
    }

    printf("Server listening on port %d\n", port);

    /* Security: Accept client connection with validation */
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(client_addr));

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        fprintf(stderr, "Error: Accept failed: %s\n", strerror(errno));
        close(server_fd);
        return -1;
    }

    /* Security: Allocate buffer with NULL check */
    buffer = (char *)calloc(INITIAL_BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        close(client_fd);
        close(server_fd);
        return -1;
    }

    /* Security: Read with size validation and bounds checking */
    ssize_t bytes_read = recv(client_fd, buffer, INITIAL_BUFFER_SIZE - 1, 0);
    if (bytes_read < 0) {
        fprintf(stderr, "Error: Receive failed: %s\n", strerror(errno));
        /* Security: Clear sensitive data before freeing */
        secure_memset(buffer, 0, INITIAL_BUFFER_SIZE);
        free(buffer);
        close(client_fd);
        close(server_fd);
        return -1;
    }

    /* Security: Null-terminate received data to prevent buffer overread */
    buffer[bytes_read] = '\0';

    printf("Received: %s\n", buffer);

    /* Security: Echo back with size validation */
    if (bytes_read > 0) {
        ssize_t bytes_sent = send(client_fd, buffer, (size_t)bytes_read, 0);
        if (bytes_sent < 0) {
            fprintf(stderr, "Error: Send failed: %s\n", strerror(errno));
        } else {
            printf("Echoed %zd bytes back to client\n", bytes_sent);
        }
    }

    result = 0;

    /* Security: Clear buffer before freeing to prevent data leaks */
    secure_memset(buffer, 0, INITIAL_BUFFER_SIZE);
    free(buffer);
    buffer = NULL;

    /* Security: Close sockets in reverse order */
    close(client_fd);
    close(server_fd);

    return result;
}

int main(void) {
    /* Test cases */
    printf("=== Test Case 1: Valid port 8080 ===\n");
    runEchoServer(8080);

    printf("\n=== Test Case 2: Valid port 9000 ===\n");
    runEchoServer(9000);

    printf("\n=== Test Case 3: Invalid port 0 ===\n");
    runEchoServer(0);

    printf("\n=== Test Case 4: Invalid port -1 ===\n");
    runEchoServer(-1);

    printf("\n=== Test Case 5: Invalid port 70000 ===\n");
    runEchoServer(70000);

    return 0;
}
