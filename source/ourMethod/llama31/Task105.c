#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void print_error(const char* message) {
    ERR_print_errors_fp(stderr);
    fprintf(stderr, "%s\n", message);
}

int main() {
    const char* host = "example.com";
    int port = 443;

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();

    // Create SSL context
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        print_error("Failed to create SSL context");
        return 1;
    }

    // Create SSL object
    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        print_error("Failed to create SSL object");
        SSL_CTX_free(ctx);
        return 1;
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        print_error("Failed to create socket");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "93.184.216.34", &server_addr.sin_addr); // IP address of example.com

    // Connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        print_error("Failed to connect to server");
        close(sock);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Set up SSL connection
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) <= 0) {
        print_error("Failed to establish SSL connection");
        close(sock);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Verify certificate
    X509* cert = SSL_get_peer_certificate(ssl);
    if (!cert) {
        print_error("No certificate provided");
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return 1;
    }

    if (SSL_get_verify_result(ssl) != X509_V_OK) {
        print_error("Certificate verification failed");
        X509_free(cert);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return 1;
    }

    X509_free(cert);

    // Send request and read response
    const char* request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    SSL_write(ssl, request, strlen(request));
    char buffer[1024];
    int bytes = SSL_read(ssl, buffer, 1024);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("%s\n", buffer);
    }

    // Clean up
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    return 0;
}