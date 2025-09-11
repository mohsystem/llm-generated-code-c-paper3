#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int main() {
    srand(time(NULL)); // Initialize random number generator
    for (int i = 0; i < 5; i++) {
        printf("%d\n", generateRandomNumber(0, 100));
    }
    return 0;
}