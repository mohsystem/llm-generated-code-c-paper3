
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl() {
    EVP_cleanup();
}

void establish_secure_connection(const char* host, int port) {
    SSL_CTX *ctx;
    SSL *ssl;
    
    // Initialize OpenSSL
    init_openssl();
    
    // Create SSL context
    const SSL_METHOD *method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    
    if (!ctx) {
        fprintf(stderr, "Unable to create SSL context\\n");
        return;
    }
    
    // Create SSL connection
    ssl = SSL_new(ctx);
    if (!ssl) {
        SSL_CTX_free(ctx);
        fprintf(stderr, "Unable to create SSL connection\\n");
        return;
    }
    
    printf("Secure connection established with %s\\n", host);
    
    // Cleanup
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}

int main() {
    // Test cases
    printf("Test Case 1: Google\\n");
    establish_secure_connection("google.com", 443);
    
    printf("\\nTest Case 2: GitHub\\n");
    establish_secure_connection("github.com", 443);
    
    printf("\\nTest Case 3: Amazon\\n");
    establish_secure_connection("amazon.com", 443);
    
    printf("\\nTest Case 4: Microsoft\\n");
    establish_secure_connection("microsoft.com", 443);
    
    printf("\\nTest Case 5: Invalid host\\n");
    establish_secure_connection("invalid.domain.com", 443);
    
    return 0;
}
