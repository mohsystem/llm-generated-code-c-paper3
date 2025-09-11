#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *s) {
    int num;
    char *endptr;
    num = strtol(s, &endptr, 10);
    if (*endptr != '\0') {
        return -1; // Conversion failed
    }
    return num;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
         printf("%d\n", stringToInt(argv[1]));
    }

    printf("%d\n", stringToInt("1234"));
    printf("%d\n", stringToInt("0"));
    printf("%d\n", stringToInt("-567"));
    printf("%d\n", stringToInt("abc"));

    return 0;
}