
#include <stdio.h>
#include <string.h>

#define KEY "MySecretKey12345"
#define MAX_LENGTH 1000

char* encrypt(const char* input) {
    static char result[MAX_LENGTH * 2 + 1];  // *2 for hex representation + null terminator
    char temp[MAX_LENGTH];
    int keyLen = strlen(KEY);
    int inputLen = strlen(input);
    int i;
    
    // XOR encryption
    for(i = 0; i < inputLen; i++) {
        temp[i] = input[i] ^ KEY[i % keyLen];
    }
    temp[i] = '\\0';
    
    // Convert to hex string
    for(i = 0; i < inputLen; i++) {
        sprintf(result + (i * 2), "%02x", (unsigned char)temp[i]);
    }
    result[inputLen * 2] = '\\0';
    
    return result;
}

int main() {
    const char* testCases[] = {
        "Hello World",
        "SecretMessage123",
        "Test@123",
        "Special$Characters#",
        "LongTextToEncrypt12345"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Original: %s\\n", testCases[i]);
        printf("Encrypted: %s\\n\\n", encrypt(testCases[i]));
    }
    
    return 0;
}
