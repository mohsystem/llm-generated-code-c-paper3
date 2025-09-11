#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

char *longest(const char *s1, const char *s2) {
    char *combined = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(combined, s1);
    strcat(combined, s2);

    int char_counts[26] = {0};
    for (int i = 0; combined[i] != '\0'; i++) {
        if (combined[i] >= 'a' && combined[i] <= 'z') {
            char_counts[combined[i] - 'a'] = 1;
        }
    }

    char *result = (char *)malloc(27); // Max 26 unique chars + null terminator
    int result_len = 0;
    for (int i = 0; i < 26; i++) {
        if (char_counts[i]) {
            result[result_len++] = 'a' + i;
        }
    }
    result[result_len] = '\0';
    qsort(result, result_len, sizeof(char), compare_chars);

    free(combined);
    return result;
}

int main() {
    char *result1 = longest("xyaabbbccccdefww", "xxxxyyyyabklmopq");
    printf("%s\n", result1); // abcdefklmopqwxy
    free(result1);

    char *result2 = longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    printf("%s\n", result2); // abcdefghijklmnopqrstuvwxyz
    free(result2);


    char *result3 = longest("", "");
    printf("%s\n", result3); //
    free(result3);

    char *result4 = longest("abcdefg", "hijklmn");
    printf("%s\n", result4); // abcdefghijklmn
    free(result4);

    char *result5 = longest("aabbccddeeff", "aabbccddeeff");
    printf("%s\n", result5); // abcdef
    free(result5);
    return 0;
}