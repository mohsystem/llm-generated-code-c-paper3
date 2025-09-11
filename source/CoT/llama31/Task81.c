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
    SHA256(X509_to_CBB(cert, NULL)->data, X509_to_CBB(cert, NULL)->len, hash);

    // Convert byte array to hex string
    char hexHash[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hexHash + i * 2, "%02x", hash[i]);
    }
    hexHash[SHA256_DIGEST_LENGTH * 2] = '\0';

    X509_free(cert);
    return strcmp(hexHash, knownHash) == 0;
}

int main() {
    const char* certificatePath = "path/to/your/certificate.crt";
    const char* knownHash = "your_known_hash_here";

    // Test cases
    printf("%d\n", checkCertificateHash(certificatePath, knownHash));
    printf("%d\n", checkCertificateHash(certificatePath, "wrong_hash"));
    printf("%d\n", checkCertificateHash("wrong_path", knownHash));
    printf("%d\n", checkCertificateHash("wrong_path", "wrong_hash"));
    printf("%d\n", checkCertificateHash(NULL, knownHash));

    return 0;
}