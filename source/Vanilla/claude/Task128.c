
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateToken(char* result, int length) {
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int i;
    for(i = 0; i < length; i++) {
        int index = rand() % (strlen(chars));
        result[i] = chars[index];
    }
    result[length] = '\\0';
}

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL));
    char token[17];  // Max length 16 + null terminator
    
    // Test case 1: Generate 8 character token
    generateToken(token, 8);
    printf("Token (8 chars): %s\\n", token);
    
    // Test case 2: Generate 12 character token
    generateToken(token, 12);
    printf("Token (12 chars): %s\\n", token);
    
    // Test case 3: Generate random number between 1-100
    printf("Random number (1-100): %d\\n", generateRandomNumber(1, 100));
    
    // Test case 4: Generate random number between -50 to 50
    printf("Random number (-50 to 50): %d\\n", generateRandomNumber(-50, 50));
    
    // Test case 5: Generate 16 character token
    generateToken(token, 16);
    printf("Token (16 chars): %s\\n", token);
    
    return 0;
}
