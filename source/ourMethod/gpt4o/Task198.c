#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    while (1) {
        int num = (rand7() - 1) * 7 + rand7(); // Generate a number from 1 to 49
        if (num <= 40) { // Use numbers 1 to 40 to map to 1 to 10
            return (num - 1) % 10 + 1;
        }
    }
}

int main() {
    srand(time(NULL));
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4, n5 = 5;
    for (int i = 0; i < n1; i++) {
        printf("%d\n", rand10());
    }
    for (int i = 0; i < n2; i++) {
        printf("%d\n", rand10());
    }
    for (int i = 0; i < n3; i++) {
        printf("%d\n", rand10());
    }
    for (int i = 0; i < n4; i++) {
        printf("%d\n", rand10());
    }
    for (int i = 0; i < n5; i++) {
        printf("%d\n", rand10());
    }
    return 0;
}