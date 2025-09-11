#include<stdio.h>
#include<string.h>
#include<ctype.h>

void encrypt(char* text, int key) {
    int n = strlen(text);
    for (int i = 0; i < n; i++) {
        if (isupper(text[i]))
            text[i] = (text[i] + key - 65) % 26 + 65;
        else
            text[i] = (text[i] + key - 97) % 26 + 97;
    }
}

int main() {
    char text[50];
    strcpy(text, "HELLO");
    encrypt(text, 3);
    printf("%s\n", text);  // Expected output: "KHOOR"

    strcpy(text, "WORLD");
    encrypt(text, 5);
    printf("%s\n", text);  // Expected output: "BTWQI"

    strcpy(text, "JAVA");
    encrypt(text, 10);
    printf("%s\n", text);  // Expected output: "TFKO"

    strcpy(text, "PROGRAMMING");
    encrypt(text, 15);
    printf("%s\n", text);  // Expected output: "UWLYHTTVRZZL"

    strcpy(text, "CYBERSECURITY");
    encrypt(text, 20);
    printf("%s\n", text);  // Expected output: "GCEVWICYVCUBC"

    return 0;
}