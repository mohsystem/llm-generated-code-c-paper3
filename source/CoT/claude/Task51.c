
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

char* encrypt(char* text) {
    if (text == NULL || strlen(text) == 0) {
        return "";
    }
    
    static char encrypted[MAX_LENGTH];
    const int SHIFT = 3; // Caesar cipher shift value
    int i;
    
    for (i = 0; text[i] != '\\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            encrypted[i] = ((text[i] - base + SHIFT) % 26) + base;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[i] = '\\0';
    
    return encrypted;
}

int main() {
    char* tests[] = {
        "Hello World!",
        "OpenAI",
        "Testing123",
        "ENCRYPT this",
        "Special@#$Characters"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Original: %s\\n", tests[i]);
        printf("Encrypted: %s\\n\\n", encrypt(tests[i]));
    }
    
    return 0;
}
