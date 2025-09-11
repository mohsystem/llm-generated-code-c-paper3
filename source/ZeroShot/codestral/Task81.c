// C doesn't have built-in support for SSL certificate validation.
// You would need to use a library like OpenSSL to implement this.
// Here's a simple example of how you might use OpenSSL to calculate the SHA-256 hash of a certificate:

#include <openssl/x509.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

int isCertificateValid(X509* cert, const char* knownHash) {
    unsigned char md[SHA256_DIGEST_LENGTH];
    unsigned int n;
    if (!X509_digest(cert, EVP_sha256(), md, &n)) {
        return 0;
    }
    if (strlen(knownHash) != n * 2) {
        return 0;
    }
    for (unsigned int i = 0; i < n; i++) {
        if (sprintf(&knownHash[i * 2], "%02x", md[i]) != 2) {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Add test cases here
    return 0;
}