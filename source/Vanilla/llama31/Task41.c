#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

void processString(char* input) {
    int len = strlen(input);
    int start = 0;
    while (start < len && input[start] == ' ') {
        start++;
    }
    int end = len - 1;
    while (end >= 0 && input[end] == ' ') {
        end--;
    }
    if (start <= end) {
        printf("Processed string: %.*s\n", end - start + 1, input + start);
    } else {
        printf("Processed string: \n");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    for (int i = 0; i < 5; i++) {
        printf("Enter a string: ");
        if (fgets(input, MAX_INPUT_LENGTH, stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // Remove newline character
            processString(input);
        }
    }
    return 0;
}