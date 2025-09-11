#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

int main() {
    char concatenatedString[MAX_LENGTH] = "";
    char input[MAX_LENGTH];
    printf("Enter strings to concatenate (enter 'stop' to finish):\n");
    while (1) {
        fgets(input, MAX_LENGTH, stdin);
        input[strcspn(input, "\n")] = 0; // remove newline character
        if (strcmp(input, "stop") == 0) {
            break;
        }
        strcat(concatenatedString, input);
    }
    printf("Concatenated string: %s\n", concatenatedString);
    return 0;
}