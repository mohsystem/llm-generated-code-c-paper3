//  For C, OpenSSL library is commonly used for SSL/TLS functionality.
//  This requires additional setup and linking with the OpenSSL library,
//  which is beyond the scope of a simple code snippet. 
//  The following is a simplified illustration assuming OpenSSL is available.

/*
#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


SSL_CTX *create_ssl_context() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        return NULL;
    }

    return ctx;
}

int create_ssl_socket(const char *host, int port) {
    int sockfd;
    struct sockaddr_in6 server_addr;
    SSL_CTX *ctx;
    SSL *ssl;

    // Create IPv6 socket
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(port);

    if (inet_pton(AF_INET6, host, &server_addr.sin6_addr) <= 0) {
        perror("Invalid address or address not supported");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // SSL context and connection
    ctx = create_ssl_context();
    if (!ctx) {
        close(sockfd);
        return -1;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) != 1) {
        perror("SSL connect failed");
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }
     // Successfully created and connected
     SSL_free(ssl); // Free the SSL structure as it is no longer used
     SSL_CTX_free(ctx);
     return sockfd;


}


int main() {
    char *hosts[] = {"google.com", "yahoo.com", "example.com", "wikipedia.org", "github.com"};
    int port = 443;
    int num_hosts = sizeof(hosts) / sizeof(hosts[0]);

    for (int i = 0; i < num_hosts; i++) {
        int sockfd = create_ssl_socket(hosts[i], port);
        if (sockfd > 0) {
            printf("Connected to %s:%d\n", hosts[i], port);
            close(sockfd);
        } else {
            printf("Failed to connect to %s:%d\n", hosts[i], port);
        }

    }

    return 0;

}

*/
// Remove the above /* and */  to run the C code after installing and linking against the OpenSSL library.