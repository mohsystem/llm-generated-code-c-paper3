#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *text, int shift) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isupper(text[i]))
            text[i] = ((text[i] + shift - 65) % 26 + 65);
        else
            text[i] = ((text[i] + shift - 97) % 26 + 97);
    }
}

int main() {
    char text[6];
    strcpy(text, "HELLO");
    encrypt(text, 4);
    printf("%s\n", text); // Outputs: LIPPS
    strcpy(text, "WORLD");
    encrypt(text, 3);
    printf("%s\n", text); // Outputs: ZRUOG
    strcpy(text, "PYTHON");
    encrypt(text, 2);
    printf("%s\n", text); // Outputs: RZVJP
    strcpy(text, "JAVA");
    encrypt(text, 1);
    printf("%s\n", text); // Outputs: KBWB
    strcpy(text, "C++");
    encrypt(text, 5);
    printf("%s\n", text); // Outputs: H++
    return 0;
}