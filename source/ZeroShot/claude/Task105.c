
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PORT 443

SSL_CTX* create_ssl_context() {
    SSL_CTX* ctx;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        return NULL;
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_verify_depth(ctx, 4);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    if (!SSL_CTX_set_default_verify_paths(ctx)) {
        SSL_CTX_free(ctx);
        return NULL;
    }

    return ctx;
}

int establish_connection(const char* hostname, SSL_CTX* ctx) {
    SSL* ssl;
    int sock;
    struct hostent* host;
    struct sockaddr_in addr;

    host = gethostbyname(hostname);
    if (!host) {
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DEFAULT_PORT);
    addr.sin_addr = *((struct in_addr*)host->h_addr);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        close(sock);
        return -1;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, hostname);

    if (SSL_connect(ssl) != 1) {
        SSL_free(ssl);
        close(sock);
        return -1;
    }

    SSL_free(ssl);
    close(sock);
    return 0;
}

int main() {
    const char* hosts[] = {
        "github.com",
        "google.com",
        "microsoft.com",
        "amazon.com",
        "oracle.com"
    };
    int num_hosts = 5;
    SSL_CTX* ctx;

    ctx = create_ssl_context();
    if (!ctx) {
        fprintf(stderr, "Failed to create SSL context\\n");
        return 1;
    }

    for (int i = 0; i < num_hosts; i++) {
        printf("Testing connection to: %s\\n", hosts[i]);
        
        if (establish_connection(hosts[i], ctx) == 0) {
            printf("Successfully established secure connection to %s\\n", hosts[i]);
        } else {
            printf("Failed to connect to %s\\n", hosts[i]);
        }
    }

    SSL_CTX_free(ctx);
    return 0;
}
