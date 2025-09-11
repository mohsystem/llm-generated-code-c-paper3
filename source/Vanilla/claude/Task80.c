
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

SSL* create_ssl_socket(const char* host, int port) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        fprintf(stderr, "Failed to create SSL context\\n");
        return NULL;
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    if (getaddrinfo(host, port_str, &hints, &res) != 0) {
        SSL_CTX_free(ctx);
        fprintf(stderr, "Failed to resolve host\\n");
        return NULL;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        fprintf(stderr, "Failed to create socket\\n");
        return NULL;
    }

    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        close(sock);
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        fprintf(stderr, "Failed to connect\\n");
        return NULL;
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    
    if (SSL_connect(ssl) != 1) {
        SSL_free(ssl);
        close(sock);
        freeaddrinfo(res);
        SSL_CTX_free(ctx);
        fprintf(stderr, "SSL connection failed\\n");
        return NULL;
    }

    freeaddrinfo(res);
    return ssl;
}

int main() {
    // Test case 1
    SSL* socket1 = create_ssl_socket("google.com", 443);
    if (socket1) {
        printf("Test 1: Connected to google.com:443\\n");
        SSL_free(socket1);
    }

    // Test case 2
    SSL* socket2 = create_ssl_socket("github.com", 443);
    if (socket2) {
        printf("Test 2: Connected to github.com:443\\n");
        SSL_free(socket2);
    }

    // Test case 3
    SSL* socket3 = create_ssl_socket("microsoft.com", 443);
    if (socket3) {
        printf("Test 3: Connected to microsoft.com:443\\n");
        SSL_free(socket3);
    }

    // Test case 4
    SSL* socket4 = create_ssl_socket("amazon.com", 443);
    if (socket4) {
        printf("Test 4: Connected to amazon.com:443\\n");
        SSL_free(socket4);
    }

    // Test case 5
    SSL* socket5 = create_ssl_socket("facebook.com", 443);
    if (socket5) {
        printf("Test 5: Connected to facebook.com:443\\n");
        SSL_free(socket5);
    }

    return 0;
}
