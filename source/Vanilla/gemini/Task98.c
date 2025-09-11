#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertToInt(const char *input) {
    char *endptr;
    long int result = strtol(input, &endptr, 10);
    if (*endptr != '\0') {
        return -1; // Indicate error if conversion failed
    }
    if (result > 2147483647 || result < -2147483648)
    {
        return -1;
    }

    return (int)result;

}

int main() {
    printf("%d\n", convertToInt("123"));
    printf("%d\n", convertToInt("456.7"));
    printf("%d\n", convertToInt("abc"));
    printf("%d\n", convertToInt("-789"));
    printf("%d\n", convertToInt("0"));
    return 0;
}