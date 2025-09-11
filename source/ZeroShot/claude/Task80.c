
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SSL* create_secure_socket(const char* host, int port) {
    // Initialize OpenSSL
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    // Create IPv6 socket
    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Failed to create socket\\n");
        return NULL;
    }

    // Set up address structure
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port);
    if (inet_pton(AF_INET6, host, &addr.sin6_addr) <= 0) {
        close(sock);
        fprintf(stderr, "Invalid address\\n");
        return NULL;
    }

    // Connect socket
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        fprintf(stderr, "Connection failed\\n");
        return NULL;
    }

    // Create SSL context
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        close(sock);
        fprintf(stderr, "Failed to create SSL context\\n");
        return NULL;
    }

    // Configure SSL context
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_verify_depth(ctx, 4);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);

    // Create SSL connection
    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        close(sock);
        SSL_CTX_free(ctx);
        fprintf(stderr, "Failed to create SSL object\\n");
        return NULL;
    }

    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        fprintf(stderr, "SSL connection failed\\n");
        return NULL;
    }

    return ssl;
}

int main() {
    // Test case 1: Connect to localhost
    SSL* s1 = create_secure_socket("::1", 443);
    if (s1) {
        printf("Test 1: Successfully connected to localhost\\n");
        SSL_free(s1);
    }

    // Test case 2: Connect to IPv6 Google
    SSL* s2 = create_secure_socket("2404:6800:4003:c04::64", 443);
    if (s2) {
        printf("Test 2: Successfully connected to Google IPv6\\n");
        SSL_free(s2);
    }

    // Test case 3: Connect to localhost different port
    SSL* s3 = create_secure_socket("::1", 8443);
    if (s3) {
        printf("Test 3: Successfully connected to localhost:8443\\n");
        SSL_free(s3);
    }

    // Test case 4: Connect to IPv6 Facebook
    SSL* s4 = create_secure_socket("2a03:2880:f003:c07:face:b00c:0:1", 443);
    if (s4) {
        printf("Test 4: Successfully connected to Facebook IPv6\\n");
        SSL_free(s4);
    }

    // Test case 5: Connect to IPv6 Amazon
    SSL* s5 = create_secure_socket("2600:1f18:22:ce00:face:b00c:0:3", 443);
    if (s5) {
        printf("Test 5: Successfully connected to Amazon IPv6\\n");
        SSL_free(s5);
    }

    return 0;
}
