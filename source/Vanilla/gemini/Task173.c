#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort
int cmpfunc(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

char *longestDupSubstring(char *s) {
    int n = strlen(s);
    if (n < 2) {
        return "";
    }

    char *suffixes[n];
    for (int i = 0; i < n; i++) {
        suffixes[i] = s + i;
    }

    qsort(suffixes, n, sizeof(char *), cmpfunc);

    int lcp[n];
    for (int i = 1; i < n; i++) {
        int j = 0;
        while (suffixes[i - 1][j] != '\0' && suffixes[i][j] != '\0' && suffixes[i - 1][j] == suffixes[i][j]) {
            j++;
        }
        lcp[i] = j;
    }
    
    int maxLen = 0;
    int startIndex = -1;
    for (int i = 1; i < n; i++) {
        if (lcp[i] > maxLen) {
            maxLen = lcp[i];
            startIndex = suffixes[i] - s;
        }
    }

    if(startIndex == -1) return "";

    char* result = (char*)malloc(sizeof(char) * (maxLen + 1));
    strncpy(result, s + startIndex, maxLen);
    result[maxLen] = '\0';
    return result;
}

int main() {
    char *result1 = longestDupSubstring("banana");
    printf("%s\n", result1); // Output: ana
    free(result1);

    char *result2 = longestDupSubstring("abcd");
    printf("%s\n", result2); // Output: 
    free(result2);
    
    char *result3 = longestDupSubstring("aa");
    printf("%s\n", result3); // Output: a
    free(result3);

    char *result4 = longestDupSubstring("aabcaabdaab");
    printf("%s\n", result4); // Output: aab
    free(result4);

    char *result5 = longestDupSubstring("bananaana");
    printf("%s\n", result5); // Output: ana
    free(result5);

    return 0;
}