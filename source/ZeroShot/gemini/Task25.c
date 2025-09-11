#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **number(char **lines, int lines_count) {
    char **numberedLines = (char **)malloc(lines_count * sizeof(char *));
    for (int i = 0; i < lines_count; i++) {
        int line_len = strlen(lines[i]);
        int num_len = snprintf(NULL, 0, "%d: ", i + 1);
        numberedLines[i] = (char *)malloc((num_len + line_len + 1) * sizeof(char));
        sprintf(numberedLines[i], "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

int main() {
    char **test1 = NULL;
    char **result1 = number(test1, 0);
    if (result1 == NULL) {
      printf("[]\n");
    }


    char *test2[] = {"a", "b", "c"};
    char **result2 = number(test2, 3);
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" ", result2[i]);
        free(result2[i]);
    }
    free(result2);
    printf("\n");

    char *test3[] = {"apple", "banana", "cherry", "date"};
    char **result3 = number(test3, 4);
    for (int i = 0; i < 4; i++) {
        printf("\"%s\" ", result3[i]);
        free(result3[i]);
    }
    free(result3);
    printf("\n");


    char *test4[] = {""};
    char **result4 = number(test4, 1);
    for (int i = 0; i < 1; i++) {
        printf("\"%s\" ", result4[i]);
        free(result4[i]);
    }
    free(result4);
    printf("\n");

    char *test5[] = {"line1", "line2", ""};
    char **result5 = number(test5, 3);
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" ", result5[i]);
        free(result5[i]);
    }
    free(result5);
    printf("\n");


    return 0;
}