#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/x509.h>
#include <openssl/sha.h>

bool checkCertificateHash(const char* certificatePath, const char* knownHash) {
    FILE* file = fopen(certificatePath, "rb");
    if (!file) return false;

    X509* cert = PEM_read_X509(file, NULL, NULL, NULL);
    fclose(file);
    if (!cert) return false;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)cert->data, cert->length, hash);

    char certHash[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(certHash + i * 2, "%02x", hash[i]);
    }
    certHash[SHA256_DIGEST_LENGTH * 2] = '\0';

    X509_free(cert);
    return strcmp(certHash, knownHash) == 0;
}

int main() {
    const char* certificatePath = "path/to/your/certificate.crt";
    const char* knownHash = "your_known_hash_here";

    printf("Does the certificate match the known hash? %s\n", checkCertificateHash(certificatePath, knownHash) ? "Yes" : "No");

    // Test cases
    printf("Test Case 1: %s\n", checkCertificateHash("path/to/cert1.crt", "hash1") ? "Yes" : "No");
    printf("Test Case 2: %s\n", checkCertificateHash("path/to/cert2.crt", "hash2") ? "Yes" : "No");
    printf("Test Case 3: %s\n", checkCertificateHash("path/to/cert3.crt", "hash3") ? "Yes" : "No");
    printf("Test Case 4: %s\n", checkCertificateHash("path/to/cert4.crt", "hash4") ? "Yes" : "No");
    printf("Test Case 5: %s\n", checkCertificateHash("path/to/cert5.crt", "hash5") ? "Yes" : "No");

    return 0;
}