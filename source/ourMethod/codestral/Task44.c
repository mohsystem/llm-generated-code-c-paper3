#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_valid_number(const char* input) {
    while (*input != '\0') {
        if (!isdigit(*input)) {
            return 0;
        }
        input++;
    }
    return 1;
}

int main() {
    char input[256];
    printf("Enter a number: ");
    fgets(input, 256, stdin);
    if (is_valid_number(input)) {
        int number = atoi(input);
        // Perform operations here
    } else {
        printf("Invalid input");
    }
    return 0;
}