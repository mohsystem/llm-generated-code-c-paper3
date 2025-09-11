#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* encrypt(char* text, int s) {
    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            text[i] = (char)((text[i] - 'A' + s) % 26 + 'A');
        } else if (islower(text[i])) {
            text[i] = (char)((text[i] - 'a' + s) % 26 + 'a');
        }
    }
    return text;
}

void mainFunction() {
    char text[] = "ATTACKATONCE";
    int s = 4;
    printf("Text : %s\n", text);
    printf("Shift : %d\n", s);
    printf("Cipher: %s\n", encrypt(text, s));

    // Test cases
    printf("Test Case 1:\n");
    char text1[] = "HELLO";
    printf("Text : %s\n", text1);
    printf("Shift : 3\n");
    printf("Cipher: %s\n", encrypt(text1, 3));

    printf("Test Case 2:\n");
    char text2[] = "WORLD";
    printf("Text : %s\n", text2);
    printf("Shift : 1\n");
    printf("Cipher: %s\n", encrypt(text2, 1));

    printf("Test Case 3:\n");
    char text3[] = "abcdef";
    printf("Text : %s\n", text3);
    printf("Shift : 2\n");
    printf("Cipher: %s\n", encrypt(text3, 2));

    printf("Test Case 4:\n");
    char text4[] = "ABCDEF";
    printf("Text : %s\n", text4);
    printf("Shift : 5\n");
    printf("Cipher: %s\n", encrypt(text4, 5));

    printf("Test Case 5:\n");
    char text5[] = "Hello, World!";
    printf("Text : %s\n", text5);
    printf("Shift : 7\n");
    printf("Cipher: %s\n", encrypt(text5, 7));
}

int main() {
    mainFunction();
    return 0;
}