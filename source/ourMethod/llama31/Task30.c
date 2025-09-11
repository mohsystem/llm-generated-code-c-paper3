#include <stdio.h>
#include <string.h>

char* longest(char* s1, char* s2) {
    static char result[27];
    char combined[strlen(s1) + strlen(s2) + 1];
    strcpy(combined, s1);
    strcat(combined, s2);

    int index = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        if (strchr(combined, c) != NULL) {
            result[index++] = c;
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    printf("%s\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq")); // "abcdefklmopqwxy"
    printf("%s\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz")); // "abcdefghijklmnopqrstuvwxyz"
    return 0;
}