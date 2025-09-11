#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isValidNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+') {
            return 0;
        }
    }
    return 1;
}

void convertAndPrint(const char *input) {
    if (isValidNumber(input)) {
        int number = atoi(input);
        printf("Converted integer: %d\n", number);
    } else {
        printf("Invalid input: %s\n", input);
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        convertAndPrint(argv[i]);
    }
    return 0;
}