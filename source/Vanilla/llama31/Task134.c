#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateKeys(char** keys, int n) {
    for (int i = 0; i < n; i++) {
        keys[i] = malloc(10 * sizeof(char));
        sprintf(keys[i], "Key-%d", i); // Simplified key generation
    }
}

void storeKeys(char** keys, int n) {
    printf("Storing Keys:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", keys[i]);
    }
}

void retrieveKeys() {
    printf("Retrieving Keys:\n");
    char* storedKeys[] = {"Key-0", "Key-1", "Key-2", "Key-3", "Key-4"};
    for (int i = 0; i < 5; i++) {
        printf("%s\n", storedKeys[i]);
    }
}

int main() {
    const int n = 5;
    char** keys = malloc(n * sizeof(char*));
    generateKeys(keys, n);
    // Test cases
    for (int i = 0; i < n; i++) {
        printf("Generated Key: %s\n", keys[i]);
    }
    storeKeys(keys, n);
    retrieveKeys();
    for (int i = 0; i < n; i++) {
        free(keys[i]);
    }
    free(keys);
    return 0;
}