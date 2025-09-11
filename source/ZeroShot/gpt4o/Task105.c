#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>

void establish_secure_connection(const char *host, int port) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    const SSL_METHOD *method = SSLv23_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);

    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        return;
    }

    SSL *ssl = SSL_new(ctx);
    int server = create_socket(host, port);

    if (server < 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    SSL_set_fd(ssl, server);
    if (SSL_connect(ssl) == -1) {
        ERR_print_errors_fp(stderr);
    } else {
        printf("Secure connection established with %s:%d\n", host, port);
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(server);
    SSL_CTX_free(ctx);
}

int create_socket(const char *host, int port) {
    int sockfd;
    struct sockaddr_in dest_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket");
        return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &dest_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1) {
        perror("Unable to connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main() {
    establish_secure_connection("93.184.216.34", 443); // www.example.com
    establish_secure_connection("172.217.14.206", 443); // www.google.com
    establish_secure_connection("205.251.242.103", 443); // www.amazon.com
    establish_secure_connection("157.240.11.35", 443); // www.facebook.com
    establish_secure_connection("140.82.114.3", 443); // www.github.com

    return 0;
}