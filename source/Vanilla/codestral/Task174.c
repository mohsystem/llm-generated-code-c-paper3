#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *shortestPalindrome(char *s) {
    int i = 0;
    int end = strlen(s) - 1;
    int j = end;
    while (i < j) {
        if (s[i] == s[j]) {
            i++;
            j--;
        } else {
            i = 0;
            end--;
            j = end;
        }
    }
    char *reversed = strdup(s + end + 1);
    strrev(reversed);
    char *result = malloc(strlen(reversed) + strlen(s) + 1);
    strcpy(result, reversed);
    strcat(result, s);
    free(reversed);
    return result;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // Output: "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // Output: "dcbabcd"
    return 0;
}