
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int generateRandomNumber(int min, int max) {
    if(min >= max) {
        fprintf(stderr, "Error: Max must be greater than min\\n");
        exit(1);
    }
    return min + (rand() % (max - min + 1));
}

void generateRandomToken(char* token, int length) {
    if(length <= 0) {
        fprintf(stderr, "Error: Length must be positive\\n");
        exit(1);
    }
    
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int charset_size = sizeof(charset) - 1;
    
    for(int i = 0; i < length; i++) {
        token[i] = charset[rand() % charset_size];
    }
    token[length] = '\\0';
}

int main() {
    // Initialize random seed using current time
    srand(time(NULL));
    
    // Test case 1: Generate random number between 1-100
    printf("Random number (1-100): %d\\n", generateRandomNumber(1, 100));
    
    // Test case 2: Generate random number between -50 to 50
    printf("Random number (-50-50): %d\\n", generateRandomNumber(-50, 50));
    
    // Test case 3: Generate 10 character token
    char token1[11];
    generateRandomToken(token1, 10);
    printf("Random token (10 chars): %s\\n", token1);
    
    // Test case 4: Generate 20 character token
    char token2[21];
    generateRandomToken(token2, 20);
    printf("Random token (20 chars): %s\\n", token2);
    
    // Test case 5: Generate 5 character token
    char token3[6];
    generateRandomToken(token3, 5);
    printf("Random token (5 chars): %s\\n", token3);
    
    return 0;
}
