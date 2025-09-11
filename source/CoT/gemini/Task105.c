#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void establishSSLConnection(const char* host, int port) {
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        fprintf(stderr, "Error creating SSL context.\n");
        ERR_print_errors_fp(stderr);
        return;
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        fprintf(stderr, "Error creating SSL object.\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return;
    }

    BIO* bio = BIO_new_ssl_connect(ctx);
    char hostname[256]; 
    snprintf(hostname, sizeof(hostname), "%s:%d", host, port);
    BIO_set_conn_hostname(bio, hostname);

    if (BIO_do_connect(bio) <= 0) {
        fprintf(stderr, "Error establishing SSL connection.\n");
        ERR_print_errors_fp(stderr);
        BIO_free_all(bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return;
    }

    printf("Secure connection established with %s:%d\n", host, port);

    BIO_free_all(bio);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
}

int main() {
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ERR_load_BIO_strings();

    establishSSLConnection("www.google.com", 443);
    establishSSLConnection("www.example.com", 443);
    establishSSLConnection("www.amazon.com", 443);
    // Test with invalid host
    //establishSSLConnection("invalidhost.com", 443);
    establishSSLConnection("www.wikipedia.org", 443);

    return 0;
}