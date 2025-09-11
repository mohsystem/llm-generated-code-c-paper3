#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** number(char** lines, int count) {
    char** numberedLines = (char**)malloc(sizeof(char*) * count);
    for (int i = 0; i < count; i++) {
        int lineLength = strlen(lines[i]);
        int numLength = snprintf(NULL, 0, "%d: ", i + 1);
        numberedLines[i] = (char*)malloc(sizeof(char) * (lineLength + numLength + 1));
        sprintf(numberedLines[i], "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

int main() {
    char *test1[] = {};
    char **result1 = number(test1, 0);
    if(result1 != NULL) free(result1);

    char *test2[] = {"a", "b", "c"};
    char **result2 = number(test2, 3);
    for (int i = 0; i < 3; i++) { printf("\"%s\" ", result2[i]); free(result2[i]); } printf("\n");
    free(result2);

    char *test3[] = {"apple", "banana", "cherry", "date"};
    char **result3 = number(test3, 4);
    for (int i = 0; i < 4; i++) { printf("\"%s\" ", result3[i]); free(result3[i]); } printf("\n");
    free(result3);

    char *test4[] = {""};
    char **result4 = number(test4, 1);
    for (int i = 0; i < 1; i++) { printf("\"%s\" ", result4[i]); free(result4[i]); } printf("\n");
    free(result4);

    char *test5[] = {"line1", "", "line3"};
    char **result5 = number(test5, 3);
    for (int i = 0; i < 3; i++) { printf("\"%s\" ", result5[i]); free(result5[i]); } printf("\n");
    free(result5);

    return 0;
}