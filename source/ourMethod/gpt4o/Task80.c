#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL* createSSLSocket(const char* host, int port) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        fprintf(stderr, "Unable to create SSL context\n");
        exit(EXIT_FAILURE);
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        SSL_CTX_free(ctx);
        fprintf(stderr, "Unable to create SSL structure\n");
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    int rv = getaddrinfo(host, NULL, &hints, &res);
    if (rv != 0) {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        fprintf(stderr, "getaddrinfo failed\n");
        exit(EXIT_FAILURE);
    }

    ((struct sockaddr_in6*)res->ai_addr)->sin6_port = htons(port);
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        freeaddrinfo(res);
        fprintf(stderr, "Unable to create socket\n");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        close(sockfd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        freeaddrinfo(res);
        fprintf(stderr, "Connection failed\n");
        exit(EXIT_FAILURE);
    }

    SSL_set_fd(ssl, sockfd);
    if (SSL_connect(ssl) <= 0) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        freeaddrinfo(res);
        fprintf(stderr, "SSL connection failed\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);
    return ssl;
}

int main() {
    const char* hosts[] = {"localhost", "example.com", "ipv6.google.com", "ipv6.test-ipv6.com", "ipv6.facebook.com"};
    int ports[] = {443, 443, 443, 443, 443};

    for (int i = 0; i < 5; ++i) {
        SSL* ssl = createSSLSocket(hosts[i], ports[i]);
        if (ssl) {
            printf("Connected to: %s\n", hosts[i]);
            SSL_shutdown(ssl);
            SSL_free(ssl);
        }
    }

    return 0;
}