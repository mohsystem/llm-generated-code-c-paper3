#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

void getSecurePassword(const char *str, char *result) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (*str) {
        MD5_Update(&c, str, 1);
        str++;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n)
        snprintf(&(result[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
}

int main() {
    char result[33];
    // Test cases
    getSecurePassword("password123", result);
    printf("%s\n", result);
    getSecurePassword("admin", result);
    printf("%s\n", result);
    getSecurePassword("securepass", result);
    printf("%s\n", result);
    getSecurePassword("test1234", result);
    printf("%s\n", result);
    getSecurePassword("welcome", result);
    printf("%s\n", result);
    return 0;
}