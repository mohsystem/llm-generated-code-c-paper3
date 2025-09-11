#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establishSSLConnection(const char *host, int port) {
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    ctx = SSL_CTX_new(TLSv1_2_client_method());
    if (!ctx) {
        fprintf(stderr, "Error creating SSL context.\n");
        return;
    }

    bio = BIO_new_ssl_connect(ctx);
    BIO_get_ssl(bio, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, port);
    BIO_set_conn_hostname(bio, hostname);


    if (BIO_do_connect(bio) <= 0) {
        fprintf(stderr, "Error establishing SSL connection.\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return;
    }

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    ERR_free_strings();
}

int main() {
    establishSSLConnection("www.google.com", 443);
    establishSSLConnection("www.example.com", 443);
    establishSSLConnection("www.amazon.com", 443);
    establishSSLConnection("www.github.com", 443);
    establishSSLConnection("www.yahoo.com", 443);
    return 0;
}