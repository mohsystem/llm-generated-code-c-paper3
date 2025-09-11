// C: Generating and validating CSRF tokens
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>

static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

char* generate_csrf_token() {
    unsigned char token[24];
    RAND_bytes(token, sizeof(token));

    char* result = malloc(sizeof(char) * (sizeof(token) * 4 / 3 + 4));
    int i, j;
    uint32_t octet_a, octet_b, octet_c, triple;

    for (i = 0, j = 0; i < sizeof(token); i += 3, j += 4) {
        octet_a = i < sizeof(token) ? token[i] : 0;
        octet_b = i + 1 < sizeof(token) ? token[i + 1] : 0;
        octet_c = i + 2 < sizeof(token) ? token[i + 2] : 0;

        triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        result[j] = base64_chars[(triple >> 3 * 6) & 0x3F];
        result[j + 1] = base64_chars[(triple >> 2 * 6) & 0x3F];
        result[j + 2] = base64_chars[(triple >> 1 * 6) & 0x3F];
        result[j + 3] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < sizeof(token) % 3; i++) {
        result[sizeof(token) * 4 / 3 + i] = '=';
    }

    result[sizeof(token) * 4 / 3 + i] = '\0';
    return result;
}

int is_csrf_token_valid(const char* existingToken, const char* receivedToken) {
    return strcmp(existingToken, receivedToken) == 0;
}