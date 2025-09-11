#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/rand.h>

void generateToken(char* buffer, size_t length) {
    unsigned char tokenBytes[32];
    RAND_bytes(tokenBytes, sizeof(tokenBytes));

    for (size_t i = 0; i < sizeof(tokenBytes); i++) {
        sprintf(&buffer[i * 2], "%02x", tokenBytes[i]);
    }
}

int main() {
    char token[65];
    for (int i = 0; i < 5; i++) {
        generateToken(token, sizeof(token));
        printf("Generated Token %d: %s\n", i + 1, token);
    }
    return 0;
}