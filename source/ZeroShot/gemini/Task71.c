#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringToInt(const char *input) {
    int num;
    char *endptr;

    num = strtol(input, &endptr, 10);

    if (*endptr != '\0' || (endptr == input && strlen(input) == 0)) {
        return -1; // Conversion failed
    }

    return num;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("%d\n", stringToInt(argv[1]));
    }
    printf("%d\n", stringToInt("12345"));
    printf("%d\n", stringToInt("0"));
    printf("%d\n", stringToInt("-987"));
    printf("%d\n", stringToInt("abc"));
    return 0;
}