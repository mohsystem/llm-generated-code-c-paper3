#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLineNumbers(char** lines, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
}

int main() {
    char* input[] = {"a", "b", "c"};
    int length = sizeof(input) / sizeof(input[0]);
    addLineNumbers(input, length);
    return 0;
}