#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100
#define MAX_STRINGS 100

void concatenate_strings() {
    int n;
    printf("Enter the number of strings to concatenate: ");
    scanf("%d", &n);
    getchar(); // Consume newline character

    char** inputs = (char**)malloc(n * sizeof(char*));
    if (inputs == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        inputs[i] = (char*)malloc(MAX_INPUT_LENGTH * sizeof(char));
        if (inputs[i] == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        printf("Enter string %d: ", i + 1);
        fgets(inputs[i], MAX_INPUT_LENGTH, stdin);
        inputs[i][strcspn(inputs[i], "\n")] = 0; // Remove newline character
    }

    char* result = (char*)malloc((MAX_INPUT_LENGTH * n) * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(result, inputs[i]);
    }

    printf("Concatenated String: %s\n", result);

    for (int i = 0; i < n; i++) {
        free(inputs[i]);
    }
    free(inputs);
    free(result);
}

int main() {
    concatenate_strings();
    return 0;
}