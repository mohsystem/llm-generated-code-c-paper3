
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SSL_CTX* create_context() {
    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        fprintf(stderr, "Unable to create SSL context\\n");
        return NULL;
    }
    return ctx;
}

SSL* create_ssl_connection(const char* host, int port) {
    SSL_CTX* ctx = create_context();
    if (!ctx) return NULL;
    
    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        SSL_CTX_free(ctx);
        return NULL;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    struct hostent* server = gethostbyname(host);
    if (!server) {
        close(sock);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        close(sock);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    return ssl;
}

int main() {
    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Test cases
    struct {
        const char* host;
        int port;
    } test_cases[] = {
        {"google.com", 443},
        {"github.com", 443},
        {"microsoft.com", 443},
        {"amazon.com", 443},
        {"facebook.com", 443}
    };

    for (int i = 0; i < 5; i++) {
        printf("Connecting to: %s\\n", test_cases[i].host);
        SSL* ssl = create_ssl_connection(test_cases[i].host, test_cases[i].port);
        
        if (ssl) {
            printf("Successfully connected to %s\\n", test_cases[i].host);
            SSL_shutdown(ssl);
            SSL_free(ssl);
        } else {
            printf("Failed to connect to %s\\n", test_cases[i].host);
        }
    }

    // Cleanup
    EVP_cleanup();
    return 0;
}
