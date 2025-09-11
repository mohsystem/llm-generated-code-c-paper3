#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return (rand() % 7) + 1;
}

int rand10() {
    int num = (rand7() - 1) * 7 + rand7();
    while (num > 40) {
        num = (rand7() - 1) * 7 + rand7();
    }
    return (num - 1) % 10 + 1;
}

void test(int n, int *res) {
    for (int i = 0; i < n; i++) {
        res[i] = rand10();
    }
}

int main() {
    srand(time(NULL));
    int n = 1;
    int res1[1];
    test(n, res1);
    printf("[%d]\n", res1[0]);

    n = 2;
    int res2[2];
    test(n, res2);
    printf("[%d,%d]\n", res2[0], res2[1]);

    n = 3;
    int res3[3];
    test(n, res3);
    printf("[%d,%d,%d]\n", res3[0], res3[1], res3[2]);

    n = 4;
    int res4[4];
    test(n, res4);
    printf("[%d,%d,%d,%d]\n", res4[0], res4[1], res4[2], res4[3]);

    n = 5;
    int res5[5];
    test(n, res5);
    printf("[%d,%d,%d,%d,%d]\n", res5[0], res5[1], res5[2], res5[3], res5[4]);


    return 0;
}