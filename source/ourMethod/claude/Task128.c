
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Generate random number within range
int generateRandomNumber(int min, int max) {
    if (min >= max) {
        fprintf(stderr, "Error: Max must be greater than min\\n");
        return -1;
    }
    
    // Seed with time and process ID for better randomness
    srand(time(NULL) * getpid());
    return min + (rand() % (max - min));
}

// Generate random token of specified length
char* generateRandomToken(int length) {
    if (length <= 0) {
        fprintf(stderr, "Error: Length must be positive\\n");
        return NULL;
    }
    
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int charset_length = sizeof(charset) - 1;
    
    char* token = malloc(length + 1); // +1 for null terminator
    if (token == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\\n");
        return NULL;
    }
    
    // Seed with time and process ID
    srand(time(NULL) * getpid());
    
    for (int i = 0; i < length; i++) {
        token[i] = charset[rand() % charset_length];
    }
    token[length] = '\\0';
    
    return token;
}

int main() {
    // Test case 1: Generate random number
    int num1 = generateRandomNumber(1, 100);
    if (num1 != -1) {
        printf("Random number between 1-100: %d\\n", num1);
    }
    
    // Test case 2: Generate another random number
    int num2 = generateRandomNumber(50, 150);
    if (num2 != -1) {
        printf("Random number between 50-150: %d\\n", num2);
    }
    
    // Test case 3: Generate random token
    char* token1 = generateRandomToken(16);
    if (token1) {
        printf("Random token (16 chars): %s\\n", token1);
        free(token1);
    }
    
    // Test case 4: Generate another random token
    char* token2 = generateRandomToken(32);
    if (token2) {
        printf("Random token (32 chars): %s\\n", token2);
        free(token2);
    }
    
    // Test case 5: Test invalid input
    int num3 = generateRandomNumber(100, 50);
    if (num3 != -1) {
        printf("Invalid range test: %d\\n", num3);
    }
    
    return 0;
}
