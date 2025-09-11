#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateStrings(char** inputs, int n) {
    int totalLength = 0;
    for (int i = 0; i < n; i++) {
        totalLength += strlen(inputs[i]);
    }
    char* result = (char*)malloc(totalLength + 1);
    int offset = 0;
    for (int i = 0; i < n; i++) {
        strcpy(result + offset, inputs[i]);
        offset += strlen(inputs[i]);
    }
    result[totalLength] = '\0';
    return result;
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    getchar(); // consume newline left-over
    char** inputs = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        inputs[i] = (char*)malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        fgets(inputs[i], 100, stdin);
        inputs[i][strcspn(inputs[i], "\n")] = 0; // remove trailing newline
    }
    char* result = concatenateStrings(inputs, n);
    printf("Concatenated string: %s\n", result);
    free(result);
    for (int i = 0; i < n; i++) {
        free(inputs[i]);
    }
    free(inputs);
    return 0;
}