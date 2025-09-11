#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

void concatenateStrings(char* result, int numStrings, char strings[][MAX_STRING_LENGTH]) {
    strcpy(result, "");
    for (int i = 0; i < numStrings; ++i) {
        strcat(result, strings[i]);
    }
}

int main() {
    char inputs[5][MAX_STRING_LENGTH];
    char result[MAX_STRING_LENGTH * 5] = {0};

    printf("Enter 5 strings:\n");
    for (int i = 0; i < 5; ++i) {
        fgets(inputs[i], MAX_STRING_LENGTH, stdin);
        inputs[i][strcspn(inputs[i], "\n")] = '\0'; // Remove newline character
    }

    concatenateStrings(result, 5, inputs);
    printf("Concatenated result: %s\n", result);

    return 0;
}