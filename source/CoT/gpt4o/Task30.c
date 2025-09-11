#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

char *longest(const char *s1, const char *s2) {
    int letters[26] = {0};
    for (const char *p = s1; *p; ++p) {
        letters[*p - 'a'] = 1;
    }
    for (const char *p = s2; *p; ++p) {
        letters[*p - 'a'] = 1;
    }
    
    char *result = (char *)malloc(27);
    if (!result) return NULL;

    int index = 0;
    for (int i = 0; i < 26; ++i) {
        if (letters[i]) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    char *result1 = longest("xyaabbbccccdefww", "xxxxyyyyabklmopq");
    printf("%s\n", result1); // Output: "abcdefklmopqwxy"
    free(result1);

    char *result2 = longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    printf("%s\n", result2); // Output: "abcdefghijklmnopqrstuvwxyz"
    free(result2);

    char *result3 = longest("abcd", "efgh");
    printf("%s\n", result3); // Output: "abcdefgh"
    free(result3);

    char *result4 = longest("zzz", "abc");
    printf("%s\n", result4); // Output: "abcz"
    free(result4);

    char *result5 = longest("aabbcc", "ddeeff");
    printf("%s\n", result5); // Output: "abcdef"
    free(result5);

    return 0;
}