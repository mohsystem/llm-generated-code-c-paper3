#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

void establishSSLConnection(const char* hostname, int port) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        fprintf(stderr, "Failed to create SSL context\n");
        return;
    }

    struct hostent* host = gethostbyname(hostname);
    if (!host) {
        fprintf(stderr, "Failed to resolve hostname\n");
        SSL_CTX_free(ctx);
        return;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        fprintf(stderr, "Failed to connect to host\n");
        close(sock);
        SSL_CTX_free(ctx);
        return;
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if (SSL_connect(ssl) <= 0) {
        fprintf(stderr, "Failed to establish SSL connection\n");
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return;
    }

    SSL_write(ssl, "GET / HTTP/1.1\r\nHost: ", 22);
    SSL_write(ssl, hostname, strlen(hostname));
    SSL_write(ssl, "\r\n\r\n", 4);

    char buffer[1024];
    int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = 0;
        printf("%s\n", buffer);
    }

    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
}

int main() {
    establishSSLConnection("www.example.com", 443);
    establishSSLConnection("www.google.com", 443);
    establishSSLConnection("www.github.com", 443);
    establishSSLConnection("www.stackoverflow.com", 443);
    establishSSLConnection("www.microsoft.com", 443);
    return 0;
}