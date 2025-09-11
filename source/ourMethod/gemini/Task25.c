#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **number(char **lines, int lines_count) {
    char **numberedLines = (char **)malloc(lines_count * sizeof(char *));
    for (int i = 0; i < lines_count; i++) {
        int line_len = strlen(lines[i]);
        int num_len = snprintf(NULL, 0, "%d: ", i + 1); // Check the length of the number string
        numberedLines[i] = (char *)malloc((num_len + line_len + 1) * sizeof(char)); // Allocate enough memory including the null terminator
        sprintf(numberedLines[i], "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

int main() {
    // Test cases
    char *test1[] = {};
    char **result1 = number(test1, 0);
    // No output for empty array


    char *test2[] = {"a", "b", "c"};
    char **result2 = number(test2, 3);
    for (int i = 0; i < 3; i++) {
        printf("%s ", result2[i]);
        free(result2[i]); // Free the allocated memory for each string
    }
    free(result2);
    printf("\n"); // Output: 1: a 2: b 3: c



    char *test3[] = {"Hello", "world", "!"};
    char **result3 = number(test3, 3);
    for (int i = 0; i < 3; i++) {
        printf("%s ", result3[i]);
        free(result3[i]);
    }
    free(result3);
    printf("\n"); // Output: 1: Hello 2: world 3: !

    char *test4[] = {""};
    char **result4 = number(test4, 1);
    for (int i = 0; i < 1; i++) {
        printf("%s ", result4[i]);
        free(result4[i]);
    }
    free(result4);
    printf("\n"); // Output: 1: 

    char *test5[] = {"Line 1", "Line 2", "Line 3", "Line 4"};
    char **result5 = number(test5, 4);
    for (int i = 0; i < 4; i++) {
        printf("%s ", result5[i]);
        free(result5[i]);
    }
    free(result5);
    printf("\n"); // Output: 1: Line 1 2: Line 2 3: Line 3 4: Line 4

    return 0;
}