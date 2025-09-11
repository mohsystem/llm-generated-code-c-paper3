// C does not have built-in support for SSL sockets.
// You would need to use a library like OpenSSL.
// Here's a simple example using OpenSSL.

#include <openssl/ssl.h>
#include <openssl/err.h>

SSL* createSSLSocket(const char* host, int port) {
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    BIO* bio = BIO_new_ssl_connect(ctx);
    BIO_set_conn_hostname(bio, host);
    BIO_do_connect(bio);
    SSL* ssl = BIO_get_ssl(bio);
    return ssl;
}

int main() {
    SSL* ssl = createSSLSocket("example.com", 443);
    // Do something with the socket...
    SSL_free(ssl);
    return 0;
}