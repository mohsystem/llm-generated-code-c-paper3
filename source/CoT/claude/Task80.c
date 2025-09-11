
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL* create_ssl_socket(const char* host, int port) {
    SSL_CTX* ctx;
    SSL* ssl;
    int sock;
    struct addrinfo hints, *res;
    
    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    // Create SSL context
    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    
    // Set up IPv6 connection parameters
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(host, NULL, &hints, &res) != 0) {
        SSL_CTX_free(ctx);
        return NULL;
    }
    
    // Create socket
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        return NULL;
    }
    
    // Set port in address structure
    ((struct sockaddr_in6*)res->ai_addr)->sin6_port = htons(port);
    
    // Connect
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        close(sock);
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        return NULL;
    }
    
    freeaddrinfo(res);
    
    // Create SSL connection
    ssl = SSL_new(ctx);
    if (!ssl) {
        close(sock);
        SSL_CTX_free(ctx);
        return NULL;
    }
    
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return NULL;
    }
    
    return ssl;
}

int main() {
    // Test cases
    struct {
        const char* host;
        int port;
    } test_cases[] = {
        {"ipv6.google.com", 443},
        {"2001:4860:4860::8888", 443},
        {"ipv6.test-ipv6.com", 443},
        {"2606:4700:4700::1111", 443},
        {"ipv6.l.google.com", 443}
    };
    
    for (int i = 0; i < 5; i++) {
        SSL* ssl = create_ssl_socket(test_cases[i].host, test_cases[i].port);
        if (ssl) {
            printf("Successfully connected to: %s\\n", test_cases[i].host);
            SSL_shutdown(ssl);
            SSL_free(ssl);
        } else {
            printf("Failed to connect to %s\\n", test_cases[i].host);
        }
    }
    
    return 0;
}
