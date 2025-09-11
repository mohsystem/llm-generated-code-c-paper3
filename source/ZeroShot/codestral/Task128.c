#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int bound) {
    return rand() % bound;
}

int main() {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        printf("%d\n", generateRandomNumber(100));
    }
    return 0;
}