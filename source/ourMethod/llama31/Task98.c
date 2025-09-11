#include <stdio.h>
#include <stdlib.h>

void mainFunction() {
    for (int i = 0; i < 5; i++) {
        printf("Enter an integer: ");
        char input[100];
        fgets(input, sizeof(input), stdin);
        int converted_int;
        if (sscanf(input, "%d", &converted_int) != 1) {
            printf("Invalid input. Please enter an integer.\n");
        } else {
            printf("Converted integer: %d\n", converted_int);
        }
    }
}

int main() {
    mainFunction();
    return 0;
}