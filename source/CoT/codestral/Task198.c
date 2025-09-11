#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int num = 41;
    while (num > 40) {
        num = (rand7() - 1) * 7 + rand7();
    }
    return num % 10 + 1;
}

int main() {
    srand(time(0));
    printf("%d\n", rand10()); // Test case 1
    printf("%d\n", rand10()); // Test case 2
    printf("%d\n", rand10()); // Test case 3
    return 0;
}