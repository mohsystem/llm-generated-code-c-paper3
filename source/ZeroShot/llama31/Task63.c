#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple Base64 decoding function (incomplete, for demonstration only)
char* base64Decode(const char* encoded) {
    // This is a highly simplified version and does not handle all cases.
    int len = strlen(encoded);
    char* decoded = malloc(len * 3 / 4 + 1);
    if (!decoded) return NULL;

    int decodedLen = 0;
    for (int i = 0; i < len; i += 4) {
        unsigned char b1 = encoded[i];
        unsigned char b2 = (i + 1 < len) ? encoded[i + 1] : 0;
        unsigned char b3 = (i + 2 < len) ? encoded[i + 2] : 0;
        unsigned char b4 = (i + 3 < len) ? encoded[i + 3] : 0;

        unsigned char o1 = (b1 & 0x3F) << 2 | (b2 & 0x30) >> 4;
        unsigned char o2 = (b2 & 0x0F) << 4 | (b3 & 0x3C) >> 2;
        unsigned char o3 = (b3 & 0x03) << 6 | (b4 & 0x3F);

        decoded[decodedLen++] = o1;
        if (i + 1 < len) decoded[decodedLen++] = o2;
        if (i + 2 < len) decoded[decodedLen++] = o3;
    }
    decoded[decodedLen] = '\0';
    return decoded;
}

void processRequest(const char* raw_data) {
    char* decoded = base64Decode(raw_data);
    if (decoded) {
        printf("%s\n", decoded);
        free(decoded);
    } else {
        printf("Failed to decode Base64\n");
    }
}

int main() {
    const char* testCases[] = {
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ==", // JSON example
        "PGJhc2U+PHVzZXI+Sm9obiBEb2U8L3VzZXI+PC9iYXNlPg==", // XML example
        "InvalidBase64", // Invalid Base64
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ==", // JSON example
        "PGJhc2U+PHVzZXI+Sm9obiBEb2U8L3VzZXI+PC9iYXNlPg==" // XML example
    };

    for (int i = 0; i < 5; ++i) {
        processRequest(testCases[i]);
    }

    return 0;
}