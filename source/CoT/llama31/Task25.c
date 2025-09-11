#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLineNumbers(char** lines, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
}

int main() {
    char* testCases[] = {"", "a", "b", "c"};
    char* testCases2[] = {"a", "b", "c"};
    char* testCases3[] = {NULL};

    printf("Test Case 1:\n");
    addLineNumbers(testCases, 4);
    printf("----------------------------\n");

    printf("Test Case 2:\n");
    addLineNumbers(testCases2, 3);
    printf("----------------------------\n");

    printf("Test Case 3:\n");
    addLineNumbers(testCases3, 1);
    printf("----------------------------\n");

    return 0;
}