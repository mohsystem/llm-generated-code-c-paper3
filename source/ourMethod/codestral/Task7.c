#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// ...
// Server-side code to handle client connections and authentication
// ...

// Client-side code to capture user credentials, construct login request, and send it to the server
int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4444);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char username[256], password[256];
    printf("Enter username: ");
    fgets(username, 256, stdin);
    printf("Enter password: ");
    fgets(password, 256, stdin);

    // Hash the password for secure transmission and storage
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char *hashed_password = base64_encode(hash, SHA256_DIGEST_LENGTH);

    // Send the login request to the server
    char buffer[512];
    sprintf(buffer, "%s:%s", username, hashed_password);
    send(sock, buffer, strlen(buffer), 0);

    free(hashed_password);
    close(sock);

    return 0;
}