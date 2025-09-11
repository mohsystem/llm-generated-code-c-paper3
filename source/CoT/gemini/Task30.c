#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest(const char *s1, const char *s2) {
    char distinctChars[26] = {0};
    int count = 0;

    for (int i = 0; s1[i] != '\0'; i++) {
        if (distinctChars[s1[i] - 'a'] == 0) {
            distinctChars[s1[i] - 'a'] = 1;
            count++;
        }
    }
    for (int i = 0; s2[i] != '\0'; i++) {
        if (distinctChars[s2[i] - 'a'] == 0) {
            distinctChars[s2[i] - 'a'] = 1;
            count++;
        }
    }

    char *result = (char *)malloc((count + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < 26; i++) {
        if (distinctChars[i] == 1) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';

     //Simple bubble sort for small array
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                char temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }

    return result;
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


    char *result4 = longest("a", "z");
    printf("%s\n", result4); // Output: az
    free(result4);

    char *result5 = longest("zzzzz", "aaaaa");
    printf("%s\n", result5); // Output: az
    free(result5);

    return 0;
}