#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyString(char* dest, const char* src) {
    strcpy(dest, src);
}

void concatenateStrings(char* dest, const char* str1, const char* str2) {
    strcpy(dest, str1);
    strcat(dest, str2);
}

void manipulateString(char* str, char oldChar, char newChar) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }
}

int main() {
    // Test cases
    char str1[100] = "Hello";
    char str2[100] = "World";
    char str3[100];
    char str4[200];
    char str5[100];

    copyString(str3, str1);
    concatenateStrings(str4, str1, str2);
    manipulateString(str5, str1, 'l', 'x');

    printf("Copied String: %s\n", str3);
    printf("Concatenated String: %s\n", str4);
    printf("Manipulated String: %s\n", str5);

    strcpy(str1, "this is init");
    strcpy(str2, " added now");
    copyString(str3, str1);
    concatenateStrings(str4, str1, str2);
    manipulateString(str5, str1, 'i', 'e');

    printf("Copied String: %s\n", str3);
    printf("Concatenated String: %s\n", str4);
    printf("Manipulated String: %s\n", str5);

    strcpy(str1, "test string");
    strcpy(str2, " more text");
    copyString(str3, str1);
    concatenateStrings(str4, str1, str2);
    manipulateString(str5, str1, 't', 'd');

    printf("Copied String: %s\n", str3);
    printf("Concatenated String: %s\n", str4);
    printf("Manipulated String: %s\n", str5);

    strcpy(str1, "sample text");
    strcpy(str2, " additional content");
    copyString(str3, str1);
    concatenateStrings(str4, str1, str2);
    manipulateString(str5, str1, 's', 'r');

    printf("Copied String: %s\n", str3);
    printf("Concatenated String: %s\n", str4);
    printf("Manipulated String: %s\n", str5);

    strcpy(str1, "final test");
    strcpy(str2, " last check");
    copyString(str3, str1);
    concatenateStrings(str4, str1, str2);
    manipulateString(str5, str1, 'f', 'l');

    printf("Copied String: %s\n", str3);
    printf("Concatenated String: %s\n", str4);
    printf("Manipulated String: %s\n", str5);

    return 0;
}