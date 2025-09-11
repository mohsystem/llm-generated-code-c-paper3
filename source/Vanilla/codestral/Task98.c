#include <stdio.h>
#include <stdlib.h>

int convertToInt(const char* input) {
    char* end;
    long output = strtol(input, &end, 10);
    if (end == input || *end != '\0') {
        printf("Invalid input. Please enter a number.\n");
        return 0;
    } else {
        return (int)output;
    }
}

int main() {
    char input[100];
    printf("Enter a number: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    int output = convertToInt(input);
    if (output != 0) {
        printf("The number is: %d\n", output);
    }
    return 0;
}