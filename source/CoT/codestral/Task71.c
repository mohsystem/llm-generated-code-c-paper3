#include <stdio.h>
#include <stdlib.h>

int stringToInteger(const char* input) {
    char* end;
    int num = strtol(input, &end, 10);
    if (*end != '\0') {
        return -1;
    }
    return num;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int num = stringToInteger(argv[1]);
        if (num != -1) {
            printf("Converted integer: %d\n", num);
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
        }
    } else {
        printf("Please provide a string input as a command line argument.\n");
    }
    return 0;
}