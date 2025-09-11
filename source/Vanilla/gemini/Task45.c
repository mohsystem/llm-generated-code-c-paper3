#include <stdio.h>
#include <stdlib.h>

int processInput(int num) {
    if (num < 0) {
        fprintf(stderr, "Error: Input must be non-negative.\n");
        return -1;
    }
    return num * 2;
}

int main() {
    printf("%d\n", processInput(5));
    printf("%d\n", processInput(-2));
    printf("%d\n", processInput(0));
    printf("%d\n", processInput(10));
    printf("%d\n", processInput(-5));
    return 0;
}