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
    SHA256(cert->der, cert->der_len, hash);

    char actualHash[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(actualHash + i * 2, "%02x", hash[i]);
    }
    actualHash[SHA256_DIGEST_LENGTH * 2] = '\0';

    X509_free(cert);
    return strcmp(actualHash, knownHash) == 0;
}

int main() {
    const char* certificatePaths[] = {"path/to/cert1.crt", "path/to/cert2.crt", "path/to/cert3.crt", "path/to/cert4.crt", "path/to/cert5.crt"};
    const char* knownHashes[] = {"knownhash1", "knownhash2", "knownhash3", "knownhash4", "knownhash5"};

    for (int i = 0; i < 5; ++i) {
        bool result = checkCertificateHash(certificatePaths[i], knownHashes[i]);
        printf("Certificate %d matches: %d\n", i + 1, result);
    }

    return 0;
}