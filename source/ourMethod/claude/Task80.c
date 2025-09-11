
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

SSL* create_secure_socket(const char* host, int port) {
    int ret = 0;
    int sock = -1;
    SSL_CTX* ctx = NULL;
    SSL* ssl = NULL;
    struct sockaddr_in6 addr;
    struct timeval timeout;

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Create SSL context with secure configuration
    const SSL_METHOD* method = TLS_client_method();
    if (method == NULL) {
        fprintf(stderr, "Failed to create SSL method\\n");
        goto cleanup;
    }

    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create SSL context\\n");
        goto cleanup;
    }

    // Set security level and protocols
    SSL_CTX_set_security_level(ctx, 2);
    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);

    // Create IPv6 socket
    sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Failed to create socket: %s\\n", strerror(errno));
        goto cleanup;
    }

    // Set socket timeout
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0 ||
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        fprintf(stderr, "Failed to set socket timeout: %s\\n", strerror(errno));
        goto cleanup;
    }

    // Prepare IPv6 address
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port);
    if (inet_pton(AF_INET6, host, &addr.sin6_addr) != 1) {
        fprintf(stderr, "Invalid IPv6 address\\n");
        goto cleanup;
    }

    // Connect socket
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "Failed to connect: %s\\n", strerror(errno));
        goto cleanup;
    }

    // Create SSL object and attach socket
    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        fprintf(stderr, "Failed to create SSL object\\n");
        goto cleanup;
    }

    SSL_set_fd(ssl, sock);

    // Perform SSL handshake
    if (SSL_connect(ssl) != 1) {
        fprintf(stderr, "SSL handshake failed\\n");
        goto cleanup;
    }

    // Success - return SSL object
    SSL_CTX_free(ctx);
    return ssl;

cleanup:
    // Cleanup on error
    if (ssl) SSL_free(ssl);
    if (sock >= 0) close(sock);
    if (ctx) SSL_CTX_free(ctx);
    return NULL;
}

int main() {
    // Test case 1
    SSL* sock1 = create_secure_socket("::1", 8443);
    if (sock1) {
        printf("Test 1: Connected to localhost IPv6\\n");
        SSL_free(sock1);
    }

    // Test case 2
    SSL* sock2 = create_secure_socket("2001:db8::1", 443);
    if (sock2) {
        printf("Test 2: Connected to example IPv6\\n");
        SSL_free(sock2);
    }

    // Test case 3
    SSL* sock3 = create_secure_socket("::ffff:192.0.2.128", 443);
    if (sock3) {
        printf("Test 3: Connected to IPv4-mapped IPv6\\n");
        SSL_free(sock3);
    }

    // Test case 4
    SSL* sock4 = create_secure_socket("fe80::1", 8443);
    if (sock4) {
        printf("Test 4: Connected to link-local IPv6\\n");
        SSL_free(sock4);
    }

    // Test case 5
    SSL* sock5 = create_secure_socket("2001:db8:85a3::8a2e:370:7334", 443);
    if (sock5) {
        printf("Test 5: Connected to full IPv6\\n");
        SSL_free(sock5);
    }

    return 0;
}
