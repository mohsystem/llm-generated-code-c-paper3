#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int a, b, idx;
    while (1) {
        a = rand7();
        b = rand7();
        idx = b + (a - 1) * 7;
        if (idx <= 40) {
            return 1 + (idx - 1) % 10;
        }
        a = idx - 40;
        b = rand7();
        idx = b + (a - 1) * 7;
        if (idx <= 60) {
            return 1 + (idx - 1) % 10;
        }
        a = idx - 60;
        b = rand7();
        idx = b + (a - 1) * 7;
        if (idx <= 20) {
            return 1 + (idx - 1) % 10;
        }
    }
}

int main() {
    srand(time(0));
    printf("%d\n", rand10()); // Test case 1
    printf("%d\n", rand10()); // Test case 2
    printf("%d\n", rand10()); // Test case 3
    printf("%d\n", rand10()); // Test case 4
    printf("%d\n", rand10()); // Test case 5
    return 0;
}