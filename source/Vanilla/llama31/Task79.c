#include <stdio.h>
#include <string.h>

void encrypt(char* text, int shift) {
    for (int i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = (char)(((int)ch + shift - 65) % 26 + 65);
        } else if (ch >= 'a' && ch <= 'z') {
            ch = (char)(((int)ch + shift - 97) % 26 + 97);
        }
        text[i] = ch;
    }
}

int main() {
    char texts[][30] = {"ATTACKATONCE", "HelloWorld", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz", "MixedCase123"};
    int shifts[] = {4, 3, 1, 5, 2};
    for (int i = 0; i < sizeof(texts) / sizeof(texts[0]); ++i) {
        printf("Text : %s\n", texts[i]);
        printf("Shift : %d\n", shifts[i]);
        encrypt(texts[i], shifts[i]);
        printf("Cipher: %s\n\n", texts[i]);
    }
    return 0;
}