#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(char* pat, int* lps, int n) {
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < n) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

char* shortestPalindrome(char* s) {
    int n = strlen(s);
    char* rev = (char*)malloc(n + 1);
    strcpy(rev, s);
    strrev(rev);
    char* temp = (char*)malloc(2 * n + 2);
    sprintf(temp, "%s$%s", s, rev);
    int* lps = (int*)malloc((2 * n + 2) * sizeof(int));
    computeLPSArray(temp, lps, 2 * n + 2);
    char* result = (char*)malloc(n - lps[n + 1] + n + 1);
    strncpy(result, rev, n - lps[n + 1]);
    result[n - lps[n + 1]] = '\0';
    strcat(result, s);
    free(rev);
    free(temp);
    free(lps);
    return result;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\n", shortestPalindrome("abc")); // "cbaabc"
    printf("%s\n", shortestPalindrome("racecar")); // "racecar"
    printf("%s\n", shortestPalindrome("")); // ""
    return 0;
}