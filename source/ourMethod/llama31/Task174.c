#include <stdio.h>
#include <string.h>

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    char* rev = malloc(len + 1);
    strcpy(rev, s);
    strrev(rev);
    for (int i = 0; i <= len; i++) {
        if (strncmp(s, rev + i, len - i) == 0) {
            char* result = malloc(len + i + 1);
            strncpy(result, rev, i);
            result[i] = '\0';
            strcat(result, s);
            free(rev);
            return result;
        }
    }
    free(rev);
    return NULL;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\n", shortestPalindrome("kayak")); // "kayak"
    printf("%s\n", shortestPalindrome("epaper")); // "repaper"
    printf("%s\n", shortestPalindrome("")); // ""
    return 0;
}