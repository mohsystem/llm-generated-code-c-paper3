#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establishSSLConnection(const char* host, int port) {
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        return;
    }

    SSL* ssl = SSL_new(ctx);
    if (ssl == NULL) {
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error connecting to server\n");
        close(sockfd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    SSL_set_fd(ssl, sockfd);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(sockfd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    printf("Connected to %s:%d\n", host, port);

    const char* request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    SSL_write(ssl, request, strlen(request));

    char buffer[1024];
    int bytes = SSL_read(ssl, buffer, 1024);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("%s\n", buffer);
    }

    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
}

int main() {
    const char* testCases[] = {"www.example.com", "www.google.com", "www.ssl.com", "www.acunetix.com", "www.geeksforgeeks.org"};
    for (int i = 0; i < 5; i++) {
        try {
            establishSSLConnection(testCases[i], 443);
        } catch (const char* e) {
            fprintf(stderr, "Error connecting to %s: %s\n", testCases[i], e);
        }
    }
    return 0;
}