#include <stdio.h>
#include <string.h>
#include <ctype.h>

void testStringOperations(const char* str1, const char* str2) {
    // Copying strings
    char str3[100];
    strcpy(str3, str1);
    printf("Copied string: %s\n", str3);

    // Concatenating strings
    char str4[100];
    strcpy(str4, str1);
    strcat(str4, " ");
    strcat(str4, str2);
    printf("Concatenated string: %s\n", str4);

    // Manipulating strings
    char str5[100];
    strcpy(str5, str4);
    for (int i = 0; str5[i]; i++) {
        str5[i] = toupper(str5[i]);
    }
    printf("Uppercase string: %s\n", str5);

    char str6[100];
    strcpy(str6, str4);
    for (int i = 0; str6[i]; i++) {
        str6[i] = tolower(str6[i]);
    }
    printf("Lowercase string: %s\n", str6);

    char str7[100];
    strcpy(str7, str4);
    for (int i = 0; str7[i]; i++) {
        if (str7[i] == ' ') {
            str7[i] = '_';
        }
    }
    printf("Manipulated string: %s\n", str7);
}

int main() {
    testStringOperations("Hello", "World");
    return 0;
}