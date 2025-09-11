// C does not support threads in the same way that Java and Python do.
// Therefore, I'll provide a simplified version of the solution that doesn't involve threading.

#include <stdio.h>

typedef void (*printNumber)(int);

typedef struct {
    int n;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    return obj;
}

void zero(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 0; i < obj->n; i++) {
        printNumber(0);
    }
}

void even(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 2; i <= obj->n; i += 2) {
        printNumber(i);
    }
}

void odd(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 1; i <= obj->n; i += 2) {
        printNumber(i);
    }
}

void printNumberFunc(int num) {
    printf("%d", num);
}

int main() {
    int testCases[] = {2, 3, 4, 5, 10};
    for (int i = 0; i < 5; i++) {
        int n = testCases[i];
        printf("n = %d\n", n);
        ZeroEvenOdd* obj = zeroEvenOddCreate(n);
        zero(obj, printNumberFunc);
        odd(obj, printNumberFunc);
        even(obj, printNumberFunc);
        printf("\n");
        free(obj);
    }
    return 0;
}