#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLineNumbers(char** lines, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
}

int main() {
    char* testCases[][4] = {
        {},
        {"a", "b", "c", NULL},
        {"hello", "world", NULL},
        {"line1", "line2", "line3", "line4"},
        {"single line", NULL}
    };

    int testCounts[] = {0, 3, 2, 4, 1};

    for (int i = 0; i < 5; i++) {
        addLineNumbers(testCases[i], testCounts[i]);
        printf("\n");
    }

    return 0;
}