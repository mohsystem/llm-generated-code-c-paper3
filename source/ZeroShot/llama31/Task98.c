#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertStringToInt(const char* str) {
    return atoi(str);
}

int main() {
    for (int i = 0; i < 5; i++) {
        printf("Enter a string to convert to integer: ");
        char input[1024];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character
        int result = convertStringToInt(input);
        if (result == 0 && strcmp(input, "0") != 0) {
            printf("Invalid input: Cannot convert to integer\n");
        } else {
            printf("Converted integer: %d\n", result);
        }
    }
    return 0;
}