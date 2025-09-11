#include <stdlib.h>
#include <stdio.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int num;
    do {
        num = (rand7() - 1) * 7 + rand7();
    } while (num > 40);
    return num % 10 + 1;
}

int main() {
    int n = 3;
    int result[n];
    for (int i = 0; i < n; i++) {
        result[i] = rand10();
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}