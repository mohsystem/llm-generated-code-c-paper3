#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int val = (rand7() - 1) * 7 + rand7();
    while (val > 40) {
        val = (rand7() - 1) * 7 + rand7();
    }
    return (val - 1) % 10 + 1;
}


void rand10List(int n, int *result) {
    for (int i = 0; i < n; i++) {
        result[i] = rand10();
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int n = 1;
    int result1[n];
    rand10List(n, result1);
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", result1[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("]\n");

    // Example 2
    n = 2;
    int result2[n];
    rand10List(n, result2);
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", result2[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("]\n");

    // Example 3
    n = 3;
    int result3[n];
    rand10List(n, result3);
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", result3[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("]\n");

    // Test case 4
    n = 5;
    int result4[n];
    rand10List(n, result4);
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", result4[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("]\n");

    // Test case 5
    n = 10;
    int result5[n];
    rand10List(n, result5);
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", result5[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf("]\n");

    return 0;
}