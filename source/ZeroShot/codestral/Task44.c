#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValidNumber(const char* s) {
    while (*s != '\0') {
        if (!isdigit(*s) && *s != '.' && *s != '+' && *s != '-') {
            return false;
        }
        s++;
    }
    return true;
}

int square(int num) {
    return num * num;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char input[100];
        printf("Enter a number: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // remove trailing newline
        if (isValidNumber(input)) {
            int num = atoi(input);
            printf("Number squared is: %d\n", square(num));
        } else {
            printf("Invalid input. Please enter a number.\n");
        }
    }
    return 0;
}