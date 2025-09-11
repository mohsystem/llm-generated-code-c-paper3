#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establish_ssl_connection(const char* host, int port) {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return;
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return;
    }

    BIO* bio = BIO_new_connect((char*)(malloc(strlen("ssl://") + strlen(host) + 10)));
    sprintf((char*)bio, "ssl://%s:%d", host, port);
    if (!bio) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    SSL_set_bio(ssl, bio, bio);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        BIO_free_all(bio);
        return;
    }

    const char* request = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: Close\r\n\r\n";
    SSL_write(ssl, request, strlen(request));

    char buffer[1024];
    int bytes;
    while ((bytes = SSL_read(ssl, buffer, 1024)) > 0) {
        fwrite(buffer, 1, bytes, stdout);
    }

    SSL_free(ssl);
    SSL_CTX_free(ctx);
    BIO_free_all(bio);
}

int main() {
    const char* hosts[] = {"example.com", "www.google.com", "www.facebook.com"};
    int port = 443;

    for (int i = 0; i < 3; i++) {
        establish_ssl_connection(hosts[i], port);
    }

    return 0;
}