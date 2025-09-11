#include <stdio.h>
#include <string.h>

char* encrypt(char* text) {
    char* encryptedText = (char*)malloc(strlen(text) + 1);
    for (int i = 0; text[i] != '\0'; i++) {
        encryptedText[i] = text[i] + 1;
    }
    encryptedText[strlen(text)] = '\0';
    return encryptedText;
}

int main() {
    char text1[] = "hello";
    char text2[] = "world";
    char text3[] = "test";
    char text4[] = "123";
    char text5[] = "";

    printf("%s\n", encrypt(text1));
    printf("%s\n", encrypt(text2));
    printf("%s\n", encrypt(text3));
    printf("%s\n", encrypt(text4));
    printf("%s\n", encrypt(text5));

    return 0;
}