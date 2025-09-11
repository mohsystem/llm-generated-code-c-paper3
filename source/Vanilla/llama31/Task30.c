#include <stdio.h>
#include <string.h>

void main() {
    char result[27];
    int len;

    // Test cases
    strcpy(result, longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"));
    printf("%s\n", result); // "abcdefklmopqwxy"

    strcpy(result, longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"));
    printf("%s\n", result); // "abcdefghijklmnopqrstuvwxyz"

    strcpy(result, longest("abc", "def"));
    printf("%s\n", result); // "abcdef"

    strcpy(result, longest("abc", "abc"));
    printf("%s\n", result); // "abc"

    strcpy(result, longest("", "abcdef"));
    printf("%s\n", result); // "abcdef"
}

char* longest(const char* s1, const char* s2) {
    static char combined[200];
    static char result[27];
    int i, j;

    // Combine strings
    strcpy(combined, s1);
    strcat(combined, s2);

    // Find unique letters
    result[0] = '\0';
    for (i = 'a'; i <= 'z'; ++i) {
        if (strchr(combined, i) != NULL && strchr(result, i) == NULL) {
            strncat(result, &i, 1);
        }
    }

    return result;
}