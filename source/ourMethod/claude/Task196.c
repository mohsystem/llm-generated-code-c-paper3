
// Note: C doesn't have built-in thread support and object-oriented features.
// This would require platform-specific threading libraries like pthreads.
// Below is a simplified version without actual threading.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int current;
    int state;  // 0: zero, 1: odd, 2: even
} ZeroEvenOdd;

void initZeroEvenOdd(ZeroEvenOdd* zeo, int n) {
    if (n < 1 || n > 1000) {
        fprintf(stderr, "Error: n must be between 1 and 1000\\n");
        exit(1);
    }
    zeo->n = n;
    zeo->current = 1;
    zeo->state = 0;
}

void printSequence(int n) {
    if (n < 1 || n > 1000) {
        fprintf(stderr, "Error: n must be between 1 and 1000\\n");
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        printf("0%d", i);
    }
    printf("\\n");
}

int main() {
    // Test cases
    int testCases[] = {2, 5, 1, 3, 4};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("Test case n = %d\\n", testCases[i]);
        printSequence(testCases[i]);
    }
    
    return 0;
}
