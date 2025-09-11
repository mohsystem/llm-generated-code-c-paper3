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
        int row = rand7() - 1; // 0 to 6
        int col = rand7(); // 1 to 7
        int value = row * 7 + col;
        if (value <= 40) {
            return value % 10 + 1;
        }
    }
}

int main() {
    srand(time(NULL)); // Initialize random seed
    int n = 5; // Number of test cases
    for (int i = 0; i < n; i++) {
        printf("%d\n", rand10());
    }
    return 0;
}