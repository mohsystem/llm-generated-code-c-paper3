#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int result = 40;
    while (result >= 40) {
        result = 7 * (rand7() - 1) + (rand7() - 1);
    }
    return result % 10 + 1;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int n1 = 1;
    for (int i = 0; i < n1; i++) {
        printf("%d ", rand10());
    }
    printf("\n");

    int n2 = 2;
    for (int i = 0; i < n2; i++) {
        printf("%d ", rand10());
    }
    printf("\n");

    int n3 = 3;
    for (int i = 0; i < n3; i++) {
        printf("%d ", rand10());
    }
    printf("\n");

    int n4 = 5;
    for (int i = 0; i < n4; i++) {
        printf("%d ", rand10());
    }
    printf("\n");

    int n5 = 10;
    for (int i = 0; i < n5; i++) {
        printf("%d ", rand10());
    }
    printf("\n");

    return 0;
}