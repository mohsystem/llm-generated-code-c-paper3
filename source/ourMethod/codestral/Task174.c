#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverse(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    return s;
}

char* shortestPalindrome(char* s) {
    int i = 0;
    int j = strlen(s) - 1;
    while (j >= 0) {
        if (s[i] == s[j]) {
            i++;
        }
        j--;
    }
    if (i == strlen(s)) {
        return s;
    }
    char* suffix = strdup(s + i);
    char* prefix = shortestPalindrome(strndup(s, i));
    char* result = (char*)malloc(strlen(s) + strlen(prefix) + 1);
    strcpy(result, reverse(suffix));
    strcat(result, prefix);
    strcat(result, suffix);
    free(suffix);
    free(prefix);
    return result;
}

int main() {
    char* s = shortestPalindrome(strdup("aacecaaa"));
    printf("%s\n", s);  // Expected: aaacecaaa
    free(s);
    s = shortestPalindrome(strdup("abcd"));
    printf("%s\n", s);  // Expected: dcbabcd
    free(s);
    return 0;
}