#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int val = (rand7() - 1) * 7 + rand7();
    if (val > 40) {
        return rand10();
    }
    return (val - 1) % 10 + 1;
}

int main() {
    srand(time(NULL));
    int testCases[] = {1, 2, 3, 5, 10};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        int n = testCases[i];
        for (int j = 0; j < n; j++) {
            printf("%d ", rand10());
        }
        printf("\n");
    }
    return 0;
}