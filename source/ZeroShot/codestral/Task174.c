#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char* prefix = strdup(suffix);
    int len = strlen(prefix);
    for (int k = 0; k < len / 2; k++) {
        char temp = prefix[k];
        prefix[k] = prefix[len - k - 1];
        prefix[len - k - 1] = temp;
    }
    char* result = (char*)malloc(strlen(prefix) + strlen(suffix) + strlen(s) - i + 1);
    sprintf(result, "%s%s%s", prefix, shortestPalindrome(strndup(s, i)), suffix);
    free(prefix);
    free(suffix);
    return result;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // Output: "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // Output: "dcbabcd"
    return 0;
}