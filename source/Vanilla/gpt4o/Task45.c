#include <stdio.h>

int performOperation(int a, int b) {
    return a + b;
}

int main() {
    int inputs[] = {10, 20, -5, 15, 0};
    int i;
    
    for (i = 0; i < 5; i++) {
        int input = inputs[i];
        printf("Result of operation with %d and 5: %d\n", input, performOperation(input, 5));
    }
    
    return 0;
}