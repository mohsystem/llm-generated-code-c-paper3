
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char BASE64_CHARS[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

char* generateToken(int length) {
    if(length <= 0) {
        return NULL;
    }
    
    char* token = (char*)malloc(length + 1);
    if(token == NULL) {
        return NULL;
    }
    
    // Use high-quality random number generation if available
    FILE* urandom = fopen("/dev/urandom", "rb");
    if(urandom) {
        unsigned char byte;
        for(int i = 0; i < length; i++) {
            if(fread(&byte, 1, 1, urandom) == 1) {
                token[i] = BASE64_CHARS[byte % 64];
            } else {
                token[i] = BASE64_CHARS[rand() % 64];
            }
        }
        fclose(urandom);
    } else {
        // Fallback to standard random if /dev/urandom is not available
        for(int i = 0; i < length; i++) {
            token[i] = BASE64_CHARS[rand() % 64];
        }
    }
    
    token[length] = '\\0';
    return token;
}

int main() {
    srand(time(NULL));
    
    // Test cases
    char* token;
    
    printf("Test 1: ");
    token = generateToken(16);
    if(token) {
        printf("%s\\n", token);
        free(token);
    }
    
    printf("Test 2: ");
    token = generateToken(32);
    if(token) {
        printf("%s\\n", token);
        free(token);
    }
    
    printf("Test 3: ");
    token = generateToken(8);
    if(token) {
        printf("%s\\n", token);
        free(token);
    }
    
    printf("Test 4: ");
    token = generateToken(24);
    if(token) {
        printf("%s\\n", token);
        free(token);
    }
    
    printf("Test 5: ");
    token = generateToken(48);
    if(token) {
        printf("%s\\n", token);
        free(token);
    }
    
    return 0;
}
