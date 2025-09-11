#include <stdio.h>

char findMissingLetter(char arr[], int len) {
    char expected = arr[0];
    for (int i = 1; i < len; i++) {
        expected++;
        if (arr[i] != expected) {
            return expected;
        }
    }
    return '\0'; // Should not be reached
}

int main() {
    char test1[] = {'a', 'b', 'c', 'd', 'f'};
    char test2[] = {'O', 'Q', 'R', 'S'};
    char test3[] = {'w', 'x', 'y', 'z'};
    char test4[] = {'A','B','D','E'};
     char test5[] = {'p','q','r','s'};
    int len1 = sizeof(test1) / sizeof(test1[0]);
    int len2 = sizeof(test2) / sizeof(test2[0]);
    int len3 = sizeof(test3) / sizeof(test3[0]);
    int len4 = sizeof(test4) / sizeof(test4[0]);
        int len5 = sizeof(test5) / sizeof(test5[0]);

    printf("%c\n", findMissingLetter(test1, len1)); // Output: e
    printf("%c\n", findMissingLetter(test2, len2)); // Output: P
        printf("%c\n", findMissingLetter(test3, len3));
            printf("%c\n", findMissingLetter(test4, len4));
                printf("%c\n", findMissingLetter(test5, len5));

    return 0;
}