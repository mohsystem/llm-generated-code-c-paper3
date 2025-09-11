#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(const char* str, int* lps, int length) {
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < length) {
        if (str[i] == str[len]) {
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

char* shortestPalindrome(const char* s) {
    int n = strlen(s);
    if (n == 0) return strdup("");

    char* reversed = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        reversed[i] = s[n - 1 - i];
    }
    reversed[n] = '\0';

    char* combined = (char*)malloc((2 * n + 2) * sizeof(char));
    sprintf(combined, "%s#%s", s, reversed);

    int* lps = (int*)malloc((2 * n + 1) * sizeof(int));
    computeLPSArray(combined, lps, 2 * n + 1);
    int maxPrefixLength = lps[2 * n];

    char* result = (char*)malloc((n + n - maxPrefixLength + 1) * sizeof(char));
    sprintf(result, "%s%s", reversed + n - maxPrefixLength, s);

    free(reversed);
    free(combined);
    free(lps);
    return result;
}

int main() {
    char* result;

    result = shortestPalindrome("aacecaaa");
    printf("%s\n", result); // Output: "aaacecaaa"
    free(result);

    result = shortestPalindrome("abcd");
    printf("%s\n", result); // Output: "dcbabcd"
    free(result);

    result = shortestPalindrome("racecar");
    printf("%s\n", result); // Output: "racecar"
    free(result);

    result = shortestPalindrome("");
    printf("%s\n", result); // Output: ""
    free(result);

    result = shortestPalindrome("a");
    printf("%s\n", result); // Output: "a"
    free(result);

    return 0;
}