#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int isCertMatchingHash(const char* certContent, const char* knownHash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)certContent, strlen(certContent), hash);
    char hashString[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashString + (i * 2), "%02x", hash[i]);
    }
    return strcmp(hashString, knownHash) == 0;
}

int main() {
    printf("%d\n", isCertMatchingHash("cert1", "knownHash1")); // 0
    printf("%d\n", isCertMatchingHash("cert2", "knownHash2")); // 0
    printf("%d\n", isCertMatchingHash("cert3", "knownHash3")); // 0
    printf("%d\n", isCertMatchingHash("cert4", "knownHash4")); // 0
    printf("%d\n", isCertMatchingHash("cert5", "knownHash5")); // 0
    return 0;
}