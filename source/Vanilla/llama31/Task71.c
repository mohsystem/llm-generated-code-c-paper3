// Compile and run using gcc and ./ commands
#include <stdio.h>
#include <stdlib.h>

int convert_string_to_int(const char* s) {
    char* endptr;
    long num = strtol(s, &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid integer: %s\n", s);
        return 0; // Return a default value or handle error as needed
    }
    return (int)num;
}

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        printf("Converted integer: %d\n", convert_string_to_int(argv[i]));
    }
    return 0;
}