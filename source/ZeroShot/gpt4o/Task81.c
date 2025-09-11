#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int verifySSLCertificate(const unsigned char* certificate, size_t cert_len, const unsigned char* knownHash, size_t hash_len) {
    unsigned char certHash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, certificate, cert_len);
    SHA256_Final(certHash, &sha256);
    return (memcmp(certHash, knownHash, hash_len) == 0);
}

int main() {
    unsigned char cert1[] = {0x30, 0x82, 0x01, 0x0a};  // Example certificate
    unsigned char knownHash1[] = {0x5e, 0x8d, 0x0b, 0x6a};  // Example hash

    unsigned char cert2[] = {0x30, 0x82, 0x01, 0x0b};
    unsigned char knownHash2[] = {0x5e, 0x8d, 0x0b, 0x6a};

    unsigned char cert3[] = {0x30, 0x82, 0x01, 0x0c};
    unsigned char knownHash3[] = {0x3e, 0x8d, 0x0b, 0x7b};

    unsigned char cert4[] = {0x30, 0x82, 0x01, 0x0d};
    unsigned char knownHash4[] = {0x5e, 0x8d, 0x0b, 0x6a};

    unsigned char cert5[] = {0x30, 0x82, 0x01, 0x0e};
    unsigned char knownHash5[] = {0x5e, 0x8d, 0x0b, 0x6a};

    printf("%d\n", verifySSLCertificate(cert1, sizeof(cert1), knownHash1, sizeof(knownHash1)));
    printf("%d\n", verifySSLCertificate(cert2, sizeof(cert2), knownHash2, sizeof(knownHash2)));
    printf("%d\n", verifySSLCertificate(cert3, sizeof(cert3), knownHash3, sizeof(knownHash3)));
    printf("%d\n", verifySSLCertificate(cert4, sizeof(cert4), knownHash4, sizeof(knownHash4)));
    printf("%d\n", verifySSLCertificate(cert5, sizeof(cert5), knownHash5, sizeof(knownHash5)));

    return 0;
}