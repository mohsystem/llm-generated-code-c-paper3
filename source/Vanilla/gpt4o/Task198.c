#include <stdio.h>
#include <stdlib.h>

int rand7() {
    return rand() % 7 + 1;
}

int rand10() {
    int result;
    do {
        int row = rand7();
        int col = rand7();
        int idx = (row - 1) * 7 + col;
        if (idx <= 40) {
            result = 1 + (idx - 1) % 10;
            break;
        }
    } while (1);
    return result;
}

int main() {
    int testCases[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        int n = testCases[i];
        printf("Output for n = %d: ", n);
        for (int j = 0; j < n; j++) {
            printf("%d ", rand10());
        }
        printf("\n");
    }
    return 0;
}