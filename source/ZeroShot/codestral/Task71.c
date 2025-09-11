#include <stdio.h>
#include <stdlib.h>

int convertToInteger(const char* s) {
    char* end;
    long val = strtol(s, &end, 10);
    if (end == s || *end != '\0' || val < INT_MIN || val > INT_MAX) {
        return -1;
    }
    return (int)val;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }
    printf("%d\n", convertToInteger(argv[1]));
    printf("%d\n", convertToInteger(argv[2]));
    printf("%d\n", convertToInteger(argv[3]));
    printf("%d\n", convertToInteger(argv[4]));
    printf("%d\n", convertToInteger(argv[5]));
    return 0;
}