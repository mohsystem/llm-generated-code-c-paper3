#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}


char *longest(const char *s1, const char *s2) {
    char distinctChars[26] = {0};
    int count = 0;

    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] >= 'a' && s1[i] <= 'z') {
            if (distinctChars[s1[i] - 'a'] == 0) {
                distinctChars[s1[i] - 'a'] = 1;
                count++;
            }
        }
    }

    for (int i = 0; s2[i] != '\0'; i++) {
         if (s2[i] >= 'a' && s2[i] <= 'z') {
            if (distinctChars[s2[i] - 'a'] == 0) {
                distinctChars[s2[i] - 'a'] = 1;
                count++;
            }
        }
    }


    char *sortedString = (char *)malloc(sizeof(char) * (count + 1));
    if (sortedString == NULL) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (distinctChars[i] == 1) {
            sortedString[index++] = (char)('a' + i);
        }
    }
    sortedString[index] = '\0';
    qsort(sortedString, index, sizeof(char), compare_chars);

    return sortedString;
}


int main() {
    char *result1 = longest("xyaabbbccccdefww", "xxxxyyyyabklmopq");
    printf("%s\n", result1); // Output: abcdefklmopqwxy
    free(result1);

    char *result2 = longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    printf("%s\n", result2); // Output: abcdefghijklmnopqrstuvwxyz
    free(result2);

    char *result3 = longest("", "");
    printf("%s\n", result3); // Output: 
    free(result3);

    char *result4 = longest("abc", "xyz");
    printf("%s\n", result4); // Output: abcxyz
    free(result4);

    char *result5 = longest("a", "z");
    printf("%s\n", result5); // Output: az
    free(result5);


    return 0;
}