#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLineNumbers(char** lines, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
}

int main() {
    char* testCases[][4] = {
        {},
        {"a", "b", "c", NULL},
        {"hello", "world", NULL},
        {"this", "is", "a", "test", NULL},
        {"single", NULL}
    };

    int testCasesLengths[] = {0, 3, 2, 4, 1};

    for (int i = 0; i < 5; i++) {
        addLineNumbers(testCases[i], testCasesLengths[i]);
        printf("\n");
    }

    return 0;
}