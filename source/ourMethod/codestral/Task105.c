#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    OpenSSL_add_ssl_algorithms();
    SSL_load_error_strings();
    method = TLS_client_method();
    ctx = SSL_CTX_new(method);

    bio = BIO_new_ssl_connect(ctx);
    BIO_set_conn_hostname(bio, "example.com:https");
    BIO_do_connect(bio);

    char buf[1024];
    int len;
    while ((len = BIO_read(bio, buf, sizeof(buf) - 1)) > 0) {
        buf[len] = '\0';
        printf("%s", buf);
    }

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}