#include <stdio.h>
#include <stdlib.h>

int rand7() {
    return 1 + rand() % 7;
}

int rand10() {
    while (1) {
        int num = (rand7() - 1) * 7 + rand7();
        if (num <= 40) {
            return 1 + (num - 1) % 10;
        }
    }
}

void testRand10(int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", rand10());
    }
    printf("\n");
}

int main() {
    testRand10(1);
    testRand10(2);
    testRand10(3);
    testRand10(5);
    testRand10(10);
    return 0;
}