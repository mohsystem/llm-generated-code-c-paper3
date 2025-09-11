#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    // This is a placeholder for the actual rand7() API
    // You should replace this with the actual implementation or API call
    return (rand() % 7) + 1;
}

int rand10() {
    while (true) {
        int row = rand7() - 1;
        int col = rand7();
        int value = row * 7 + col;
        if (value <= 40) {
            return value % 10 + 1;
        }
    }
}

void test_rand10(int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", rand10());
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    for (int n = 1; n <= 5; n++) {
        printf("n = %d: [", n);
        test_rand10(n);
    }
    return 0;
}