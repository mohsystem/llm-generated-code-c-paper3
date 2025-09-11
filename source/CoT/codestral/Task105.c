// Requires OpenSSL library
#include <openssl/ssl.h>
#include <openssl/err.h>

int main() {
    SSL_library_init();
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    SSL *ssl = SSL_new(ctx);
    BIO *bio = BIO_new_ssl_connect(ctx);
    BIO_set_conn_hostname(bio, "www.example.com:https");
    BIO_do_connect(bio);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}