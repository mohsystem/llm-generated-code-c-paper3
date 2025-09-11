#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void longest(char* s1, char* s2, char* result) {
    bool seen[26] = {false};
    char combined[strlen(s1) + strlen(s2) + 1];
    strcpy(combined, s1);
    strcat(combined, s2);

    int j = 0;
    for (int i = 0; i < strlen(combined); i++) {
        char c = combined[i];
        if (!seen[c - 'a']) {
            seen[c - 'a'] = true;
            result[j++] = c;
        }
    }
    result[j] = '\0';

    // Sort the result
    for (int i = 0; i < j - 1; i++) {
        for (int k = i + 1; k < j; k++) {
            if (result[i] > result[k]) {
                char temp = result[i];
                result[i] = result[k];
                result[k] = temp;
            }
        }
    }
}

int main() {
    char result[27];
    longest("xyaabbbccccdefww", "xxxxyyyyabklmopq", result);
    printf("%s\n", result); // "abcdefklmopqwxy"

    longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", result);
    printf("%s\n", result); // "abcdefghijklmnopqrstuvwxyz"

    longest("abc", "def", result);
    printf("%s\n", result); // "abcdef"

    longest("aaaa", "bbbb", result);
    printf("%s\n", result); // "ab"

    longest("", "abcdefghijklmnopqrstuvwxyz", result);
    printf("%s\n", result); // "abcdefghijklmnopqrstuvwxyz"

    return 0;
}