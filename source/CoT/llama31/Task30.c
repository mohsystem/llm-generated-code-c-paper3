// C code
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void sort(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                swap(&str[i], &str[j]);
            }
        }
    }
}

char* longest(const char* s1, const char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char* combined = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    strcpy(combined, s1);
    strcat(combined, s2);
    sort(combined);

    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    result[0] = '\0';
    bool lastChar = false;
    char lastC = '\0';

    for (int i = 0; i < strlen(combined); i++) {
        if (combined[i] != lastC) {
            strcat(result, &combined[i]);
            lastC = combined[i];
        }
    }

    free(combined);
    return result;
}

int main() {
    printf("%s\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq")); // "abcdefklmopqwxy"
    printf("%s\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz")); // "abcdefghijklmnopqrstuvwxyz"
    printf("%s\n", longest("abc", "def")); // "abcdef"
    printf("%s\n", longest("a", "b")); // "ab"
    printf("%s\n", longest("", "abc")); // "abc"
    return 0;
}