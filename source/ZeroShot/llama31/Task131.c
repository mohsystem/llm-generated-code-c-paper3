#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <base64.h>

void deserializeJSON(const char* json) {
    // Validate and sanitize input
    if (!json || strlen(json) == 0) {
        fprintf(stderr, "Invalid input data\n");
        return;
    }

    // Use digital signatures or hashing for integrity check (example with hashing)
    const char* expectedHash = "your_expected_hash_here"; // Replace with actual expected hash
    char* actualHash = hash(json);
    if (strcmp(actualHash, expectedHash) != 0) {
        fprintf(stderr, "Data integrity check failed\n");
        free(actualHash);
        return;
    }
    free(actualHash);

    // Simple JSON parsing (for demonstration; use a library like cJSON for real applications)
    char* usernameStart = strstr(json, "\"username\":\"");
    char* userRoleStart = strstr(json, "\"userRole\":\"");
    if (!usernameStart || !userRoleStart) {
        fprintf(stderr, "Invalid JSON format\n");
        return;
    }

    usernameStart += strlen("\"username\":\"");
    userRoleStart += strlen("\"userRole\":\"");

    char* usernameEnd = strchr(usernameStart, '\"');
    char* userRoleEnd = strchr(userRoleStart, '\"');

    if (!usernameEnd || !userRoleEnd) {
        fprintf(stderr, "Invalid JSON format\n");
        return;
    }

    *usernameEnd = '\0';
    *userRoleEnd = '\0';

    printf("Deserialized Data: username=%s, userRole=%s\n", usernameStart, userRoleStart);
}

char* hash(const char* input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);

    char* base64Hash = base64_encode(hash, SHA256_DIGEST_LENGTH);
    return base64Hash;
}

int main() {
    const char* testData[] = {
        "{\"username\":\"john_doe\",\"userRole\":\"admin\"}",
        "{\"username\":\"malicious\",\"userRole\":\"hacker\"}",
        "{\"username\":\"valid\",\"userRole\":\"user\"}",
        "{\"username\":\"invalid\",\"userRole\":\"invalid\"}",
        "{\"username\":\"test\",\"userRole\":\"test\"}"
    };

    for (int i = 0; i < 5; ++i) {
        deserializeJSON(testData[i]);
    }

    return 0;
}