#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

SSL* createSSLSocket(const char* host, int port) {
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return NULL;
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return NULL;
    }

    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, host, &server_addr.sin6_addr);
    server_addr.sin6_port = htons(port);

    int sock_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd < 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        ERR_print_errors_fp(stderr);
        close(sock_fd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    SSL_set_fd(ssl, sock_fd);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(sock_fd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    return ssl;
}

int main() {
    const char* hosts[] = {"::1", "ipv6.example.com"};
    int ports[] = {443, 443};

    for (int i = 0; i < 2; i++) {
        SSL* ssl = createSSLSocket(hosts[i], ports[i]);
        if (ssl) {
            printf("Connected to %s:%d\n", hosts[i], ports[i]);
            SSL_free(ssl);
        } else {
            fprintf(stderr, "Error connecting to %s:%d\n", hosts[i], ports[i]);
        }
    }

    return 0;
}