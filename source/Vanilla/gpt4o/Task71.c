#include <stdio.h>
#include <stdlib.h>

int convertToInt(const char* input) {
    return atoi(input);
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        char* endptr;
        int number = strtol(argv[i], &endptr, 10);
        if (*endptr == '\0') {
            printf("Converted integer: %d\n", number);
        } else {
            printf("Invalid input: %s\n", argv[i]);
        }
    }
    return 0;
}