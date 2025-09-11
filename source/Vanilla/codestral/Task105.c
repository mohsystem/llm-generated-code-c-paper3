#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>

int main() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    BIO *sbio;
    SSL *ssl;

    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    SSL_load_error_strings();

    method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    sbio = BIO_new_ssl_connect(ctx);
    BIO_set_conn_hostname(sbio, "example.com:443");
    if (BIO_do_connect(sbio) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    ssl = BIO_get_ssl(sbio, &sbio);
    if (ssl == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    BIO_free_all(sbio);
    SSL_CTX_free(ctx);

    return 0;
}