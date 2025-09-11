
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

typedef struct {
    SSL_CTX* ctx;
    SSL* ssl;
    BIO* bio;
} Task105;

Task105* create_ssl_client(const char* host, int port) {
    Task105* client = (Task105*)malloc(sizeof(Task105));
    if (!client) {
        return NULL;
    }
    
    // Initialize SSL library
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    // Create SSL context
    client->ctx = SSL_CTX_new(TLS_client_method());
    if (!client->ctx) {
        free(client);
        return NULL;
    }
    
    // Set security options
    SSL_CTX_set_security_level(client->ctx, 2);
    SSL_CTX_set_verify(client->ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_verify_depth(client->ctx, 4);
    
    // Load system certificates
    if (!SSL_CTX_set_default_verify_paths(client->ctx)) {
        SSL_CTX_free(client->ctx);
        free(client);
        return NULL;
    }
    
    // Create SSL structure
    client->ssl = SSL_new(client->ctx);
    if (!client->ssl) {
        SSL_CTX_free(client->ctx);
        free(client);
        return NULL;
    }
    
    // Create BIO
    char connection_str[256];
    snprintf(connection_str, sizeof(connection_str), "%s:%d", host, port);
    client->bio = BIO_new_connect(connection_str);
    if (!client->bio) {
        SSL_free(client->ssl);
        SSL_CTX_free(client->ctx);
        free(client);
        return NULL;
    }
    
    return client;
}

int establish_secure_connection(Task105* client) {
    if (!client) {
        return 0;
    }
    
    // Connect BIO
    if (BIO_do_connect(client->bio) <= 0) {
        return 0;
    }
    
    // Set up SSL on BIO
    SSL_set_bio(client->ssl, client->bio, client->bio);
    
    // Perform SSL handshake
    if (SSL_connect(client->ssl) != 1) {
        return 0;
    }
    
    // Verify certificate
    X509* cert = SSL_get_peer_certificate(client->ssl);
    if (!cert) {
        return 0;
    }
    
    long verify_result = SSL_get_verify_result(client->ssl);
    if (verify_result != X509_V_OK) {
        X509_free(cert);
        return 0;
    }
    
    X509_free(cert);
    return 1;
}

void close_connection(Task105* client) {
    if (client) {
        if (client->ssl) {
            SSL_shutdown(client->ssl);
            SSL_free(client->ssl);
        }
        if (client->ctx) {
            SSL_CTX_free(client->ctx);
        }
        free(client);
    }
}

int main() {
    // Test cases
    struct {
        const char* host;
        int port;
    } test_cases[] = {
        {"localhost", 8443},
        {"example.com", 443},
        {"securetestserver.com", 443},
        {"localhost", 9443},
        {"testssl.com", 443}
    };
    
    for (int i = 0; i < 5; i++) {
        Task105* client = create_ssl_client(test_cases[i].host, test_cases[i].port);
        if (client) {
            if (establish_secure_connection(client)) {
                printf("Test successful for %s:%d\\n", test_cases[i].host, test_cases[i].port);
            } else {
                printf("Test failed for %s:%d\\n", test_cases[i].host, test_cases[i].port);
            }
            close_connection(client);
        } else {
            printf("Failed to create client for %s:%d\\n", test_cases[i].host, test_cases[i].port);
        }
    }
    
    return 0;
}
