#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establishSSLConnection(const char *urlString) {
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    // Initialize OpenSSL
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        perror("Error creating SSL context");
        return;
    }

    // For testing only! Disable certificate verification
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);


    bio = BIO_new_ssl_connect(ctx);
    if (!bio) {
        perror("Error creating BIO");
        SSL_CTX_free(ctx);
        return;
    }
    
     char hostname[256];
    sscanf(urlString + 8, "%255[^/]", hostname); // Extract hostname


    BIO_set_conn_hostname(bio, hostname);
    BIO_set_conn_port(bio, "443");

    if (BIO_do_connect(bio) <= 0) {
        perror("Error connecting");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return;
    }

    ssl = BIO_get_ssl(bio, NULL);
    if (!ssl) {
        perror("Error getting SSL object");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return;
    }


    printf("Response Code : Connection established successfully\n");

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
}


int main() {
    establishSSLConnection("https://www.google.com");
    establishSSLConnection("https://www.example.com");
    establishSSLConnection("https://www.amazon.com");
    establishSSLConnection("https://www.bing.com");
    establishSSLConnection("https://www.github.com");
    return 0;
}