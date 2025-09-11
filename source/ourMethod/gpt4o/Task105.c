#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establishSecureConnection(const char* host, int port) {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    
    if (!ctx) {
        printf("Unable to create SSL context\n");
        return;
    }

    SSL *ssl = SSL_new(ctx);
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET, host, &sa.sin_addr);
    
    if (connect(server, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        printf("Unable to connect to %s\n", host);
        return;
    }

    SSL_set_fd(ssl, server);
    
    if (SSL_connect(ssl) <= 0) {
        printf("Error establishing SSL connection to %s\n", host);
    } else {
        const char* request = "GET / HTTP/1.1\r\n\r\n";
        SSL_write(ssl, request, strlen(request));
        char buffer[1024] = {0};
        SSL_read(ssl, buffer, sizeof(buffer));
        printf("Response from %s: %s\n", host, buffer);
    }

    SSL_free(ssl);
    close(server);
    SSL_CTX_free(ctx);
}

int main() {
    // Example Test Cases
    establishSecureConnection("93.184.216.34", 443); // www.example.com
    establishSecureConnection("142.250.190.14", 443); // www.google.com
    establishSecureConnection("98.137.11.163", 443); // www.yahoo.com
    establishSecureConnection("204.79.197.200", 443); // www.bing.com
    establishSecureConnection("140.82.121.3", 443); // www.github.com
    return 0;
}