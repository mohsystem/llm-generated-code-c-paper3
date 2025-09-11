#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** numberLines(char** lines, int lineCount) {
    char** numberedLines = (char**)malloc(sizeof(char*) * lineCount);
    for (int i = 0; i < lineCount; i++) {
        int numLength = snprintf(NULL, 0, "%d", i + 1);
        int lineLength = strlen(lines[i]);
        numberedLines[i] = (char*)malloc(sizeof(char) * (numLength + lineLength + 4)); // +4 for ": ", '\0'
        sprintf(numberedLines[i], "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

int main() {
    // Test cases
    char* test1[] = {};
    char** result1 = numberLines(test1, 0);
    // No output expected for empty array

    char* test2[] = {"a", "b", "c"};
    char** result2 = numberLines(test2, 3);
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" ", result2[i]);
        free(result2[i]);
    }
    free(result2);
    printf("\n");  // Expected: "1: a" "2: b" "3: c" 

    char* test3[] = {""};
    char** result3 = numberLines(test3, 1);
    printf("\"%s\" \n", result3[0]);
    free(result3[0]);
    free(result3); // Expected: "1: "

    char* test4[] = {"Hello", "World", "!"};
    char** result4 = numberLines(test4, 3);
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" ", result4[i]);
        free(result4[i]);
    }
    free(result4);
    printf("\n");  // Expected: "1: Hello" "2: World" "3: !"

    char* test5[] = {"Line 1", "Line 2", "Line3"};
    char** result5 = numberLines(test5, 3);
    for (int i = 0; i < 3; i++) {
        printf("\"%s\" ", result5[i]);
        free(result5[i]);
    }
    free(result5);
    printf("\n");  // Expected: "1: Line 1" "2: Line 2" "3: Line3"

    return 0;
}