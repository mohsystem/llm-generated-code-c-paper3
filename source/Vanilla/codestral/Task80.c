// C does not have built-in support for SSL sockets, so this example uses OpenSSL library.
// Remember to install and link OpenSSL library in your project.
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SSL* createSSLClientSocket(const char* host, int port) {
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);

    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, NULL, &hints, &servinfo) != 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0)
            break;
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to connect\n");
        exit(EXIT_FAILURE);
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) != 1) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);
    SSL_CTX_free(ctx);
    return ssl;
}

int main() {
    SSL* socket1 = createSSLClientSocket("example.com", 443);
    printf("Socket 1 connected: %d\n", SSL_is_init_finished(socket1));
    // Repeat for other test cases
    return 0;
}