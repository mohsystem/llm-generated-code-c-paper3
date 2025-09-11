#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide an input string.\n");
        return 1;
    }

    char *end;
    long num = strtol(argv[1], &end, 10);

    if (*end != '\0') {
        printf("Invalid input: %s\n", argv[1]);
    } else {
        printf("Converted integer: %ld\n", num);
    }

    return 0;
}