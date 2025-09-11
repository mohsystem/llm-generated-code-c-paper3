#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char* text, int shift) {
    int n = strlen(text);
    for (int i = 0; i < n; i++) {
        if (isupper(text[i]))
            text[i] = ((text[i] + shift - 65) % 26 + 65);
        else
            text[i] = ((text[i] + shift - 97) % 26 + 97);
    }
}

void decrypt(char* text, int shift) {
    encrypt(text, 26 - shift);
}

int main() {
    char text[100] = "HELLO";
    int shift = 4;
    encrypt(text, shift);
    printf("Encrypted: %s\n", text);
    decrypt(text, shift);
    printf("Decrypted: %s\n", text);
    return 0;
}