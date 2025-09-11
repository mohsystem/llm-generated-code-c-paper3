
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char* text, int shift, char* result) {
    int len = strlen(text);
    for(int i = 0; i < len; i++) {
        if(isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            result[i] = base + ((text[i] - base + shift) % 26);
        } else {
            result[i] = text[i];
        }
    }
    result[len] = '\\0';
}

int main() {
    char result[100];
    
    // Test cases
    encrypt("Hello World!", 3, result);
    printf("%s\\n", result);  // "Khoor Zruog!"
    
    encrypt("OpenAI", 5, result);
    printf("%s\\n", result);  // "TujsFN"
    
    encrypt("ABCXYZ", 1, result);
    printf("%s\\n", result);  // "BCDYZA"
    
    encrypt("Testing123", 7, result);
    printf("%s\\n", result);  // "Alzapun123"
    
    encrypt("Crypto", 25, result);
    printf("%s\\n", result);  // "Bqxosn"
    
    return 0;
}
