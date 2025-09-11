#include <stdio.h>
#include <string.h>

void concatenateStrings(char *result, const char *strings[], int count) {
    result[0] = '\0'; // Initialize result as an empty string
    for (int i = 0; i < count; ++i) {
        strcat(result, strings[i]);
    }
}

int main() {
    char input[256];
    char *strings[50];
    char result[256];

    for (int i = 0; i < 5; ++i) {
        printf("Enter strings to concatenate (comma separated): ");
        fgets(input, 256, stdin);

        int count = 0;
        char *token = strtok(input, ",\n");
        while (token != NULL) {
            strings[count++] = token;
            token = strtok(NULL, ",\n");
        }

        concatenateStrings(result, strings, count);
        printf("Concatenated result: %s\n", result);
    }
    return 0;
}