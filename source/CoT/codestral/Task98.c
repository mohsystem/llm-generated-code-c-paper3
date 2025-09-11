#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool convertToInt(const char* input, int* number) {
    char* end;
    *number = strtol(input, &end, 10);
    if (*end != '\0') {
        return false;
    }
    return true;
}

int main() {
    for(int i = 0; i < 5; i++) {
        char input[256];
        printf("Enter a number: ");
        fgets(input, sizeof(input), stdin);
        int number;
        if (convertToInt(input, &number)) {
            printf("Converted number: %d\n", number);
        } else {
            printf("Invalid input. Please enter an integer.\n");
        }
    }
    return 0;
}