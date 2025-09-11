#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

SSL_CTX* create_ssl_context() {
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        perror("SSL_CTX_new failed");
        return NULL;
    }
    // Disable certificate verification (for testing only, NOT recommended for production)
     SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
    return ctx;
}

SSL* create_secure_socket(SSL_CTX *ctx, const char *host, int port) {
    BIO *bio = BIO_new_ssl_connect(ctx);
    if (!bio) {
        perror("BIO_new_ssl_connect failed");
        return NULL;
    }
    BIO_get_ssl(bio, &ctx);
    SSL *ssl = ctx;
    char hostname[256];
    snprintf(hostname, sizeof(hostname), "%s:%d", host, port);
    BIO_set_conn_hostname(bio, hostname);
    if (BIO_do_connect(bio) <= 0) {
        perror("BIO_do_connect failed");
        BIO_free_all(bio);
        return NULL;
    }
    return ssl;
}


int main() {
    SSL_CTX *ctx = create_ssl_context();
    if (!ctx) {
        return 1;
    }
    const char *hosts[] = {"www.google.com", "www.example.com", "www.amazon.com", "www.wikipedia.org", "www.github.com"};
    int ports[] = {443, 443, 443, 443, 443};
    
    for(int i = 0; i < 5; i++) {
        SSL *ssl = create_secure_socket(ctx, hosts[i], ports[i]);
        if (ssl) {
             printf("Connected to %s:%d using TLS\n", hosts[i], ports[i]);
            SSL_free(ssl); 
        }
    }

    SSL_CTX_free(ctx);
    return 0;
}