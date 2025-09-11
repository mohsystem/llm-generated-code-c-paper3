// This code is a simplified version and does not handle errors or cleanup.
// In a real-world application, error handling and cleanup should be added.
#include <openssl/ssl.h>
#include <arpa/inet.h>

SSL* createSSLSocket(const char* host, int port) {
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    SSL* ssl = SSL_new(ctx);
    BIO* bio = BIO_new_ssl_connect(ctx);
    BIO_set_conn_hostname(bio, host);
    BIO_do_connect(bio);
    SSL_set_fd(ssl, BIO_get_fd(bio, NULL));
    SSL_connect(ssl);
    return ssl;
}

int main() {
    SSL* ssl = createSSLSocket("example.com", 443);
    // Use the ssl here
    return 0;
}