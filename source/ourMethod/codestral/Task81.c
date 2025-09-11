#include <openssl/x509.h>
#include <openssl/sha.h>
#include <stdio.h>

int isCertificateHashMatch(X509* cert, const char* knownHash) {
    unsigned char* certBytes = nullptr;
    int certBytesLen = i2d_X509(cert, &certBytes);
    if (certBytesLen <= 0) {
        return 0;
    }

    unsigned char certHash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, certBytes, certBytesLen);
    SHA256_Final(certHash, &sha256);

    char certHashHex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(certHashHex + (i * 2), "%02x", certHash[i]);
    }
    certHashHex[SHA256_DIGEST_LENGTH * 2] = '\0';

    OPENSSL_free(certBytes);
    return strcmp(certHashHex, knownHash) == 0;
}

int main() {
    // Test cases
    // Replace with actual test cases
    return 0;
}