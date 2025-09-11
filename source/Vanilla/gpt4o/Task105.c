#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int connect_ssl(const char *host, int port) {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) return 0;

    struct hostent *host_entry = gethostbyname(host);
    if (!host_entry) return 0;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = *(long*)(host_entry->h_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) return 0;

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) == -1) return 0;

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    return 1;
}

int main() {
    printf("%d\n", connect_ssl("www.google.com", 443)); // Test case 1
    printf("%d\n", connect_ssl("www.example.com", 443)); // Test case 2
    printf("%d\n", connect_ssl("www.invalid-url.com", 443)); // Test case 3
    printf("%d\n", connect_ssl("www.github.com", 443)); // Test case 4
    printf("%d\n", connect_ssl("www.facebook.com", 443)); // Test case 5

    return 0;
}