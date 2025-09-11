#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    srand(time(NULL));
    printf("C Random Numbers:\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", generateRandomNumber(1, 100));
    }
    return 0;
}