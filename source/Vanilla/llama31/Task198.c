#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    // This is a placeholder for the actual rand7() API
    // You should replace this with the actual implementation
    return (rand() % 7) + 1;
}

int rand10() {
    while (true) {
        int i = rand7() - 1;
        int j = rand7();
        int value = i * 7 + j;
        if (value <= 40) {
            return value % 10 + 1;
        }
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    int n = 5; // Number of test cases
    for (int i = 0; i < n; i++) {
        printf("%d ", rand10());
    }
    return 0;
}