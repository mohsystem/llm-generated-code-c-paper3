#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    char input[256];
    printf("Enter an integer: ");
    fgets(input, sizeof(input), stdin);

    char* endptr;
    long num = strtol(input, &endptr, 10);

    if (*endptr != '\n' && *endptr != '\0') {
        printf("Invalid input. Please enter an integer.\n");
    } else if (num < INT_MIN || num > INT_MAX) {
        printf("Invalid input. The number is out of range.\n");
    } else {
        printf("You entered: %d\n", (int)num);
    }

    return 0;
}