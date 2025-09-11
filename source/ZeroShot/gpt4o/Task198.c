#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int num;
    do {
        int row = rand7();
        int col = rand7();
        num = (row - 1) * 7 + col;
    } while (num > 40);
    return 1 + (num - 1) % 10;
}

void testRand10(int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", rand10());
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    
    testRand10(1);
    testRand10(2);
    testRand10(3);
    testRand10(4);
    testRand10(5);
    
    return 0;
}