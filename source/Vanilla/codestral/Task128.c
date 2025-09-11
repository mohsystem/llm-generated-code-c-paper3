#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int max) {
    srand(time(0));
    return rand() % max;
}

int main() {
    printf("%d", generateRandomNumber(100)); // Test case
    return 0;
}