#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

char *longest(const char *s1, const char *s2) {
    char *combined = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(combined, s1);
    strcat(combined, s2);

    int len = strlen(combined);
    char *distinct = malloc(len + 1);
    int distinct_len = 0;
    for (int i = 0; i < len; i++) {
        int found = 0;
        for (int j = 0; j < distinct_len; j++) {
            if (combined[i] == distinct[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            distinct[distinct_len++] = combined[i];
        }
    }
    distinct[distinct_len] = '\0';

    qsort(distinct, distinct_len, sizeof(char), compare_chars);
    free(combined);
    return distinct;

}

int main() {
    char *result1 = longest("xyaabbbccccdefww", "xxxxyyyyabklmopq");
    printf("%s\n", result1);
    free(result1);

    char *result2 = longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    printf("%s\n", result2);
    free(result2);

    char *result3 = longest("", "");
    printf("%s\n", result3);
    free(result3);

    char *result4 = longest("a", "b");
    printf("%s\n", result4);
    free(result4);

    char *result5 = longest("bb", "aa");
    printf("%s\n", result5);
    free(result5);


    return 0;
}