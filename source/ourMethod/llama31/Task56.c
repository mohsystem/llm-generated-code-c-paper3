#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>
#include <base64.h>

void generateToken(char* token, size_t tokenLen) {
    // Generate a random UUID
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    
    // Generate additional random bytes
    unsigned char randomBytes[16];
    srand(time(NULL));
    for (int i = 0; i < 16; ++i) {
        randomBytes[i] = rand() % 256;
    }
    
    // Combine UUID and random bytes
    unsigned char combinedBytes[32];
    memcpy(combinedBytes, bin_uuid, 16);
    memcpy(combinedBytes + 16, randomBytes, 16);
    
    // Encode the combined bytes using Base64
    base64_encode(combinedBytes, 32, token, tokenLen);
}

int main() {
    char token[45]; // Base64 encoded string length for 32 bytes input
    generateToken(token, sizeof(token));
    printf("Generated Token: %s\n", token);
    return 0;
}