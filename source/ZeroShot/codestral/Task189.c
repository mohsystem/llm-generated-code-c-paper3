// C does not support threads directly, so a platform-specific solution or a library is required.
// This is a simplified version without threading.

#include <stdio.h>

void printNumber(int num) {
    printf("%d", num);
}

typedef struct {
    int n;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    return obj;
}

void zeroEvenOddZero(ZeroEvenOdd* obj, void(*printNumber)(int)) {
    for (int i = 0; i < obj->n; i++) {
        printNumber(0);
    }
}

void zeroEvenOddEven(ZeroEvenOdd* obj, void(*printNumber)(int)) {
    for (int i = 2; i <= obj->n; i += 2) {
        printNumber(i);
    }
}

void zeroEvenOddOdd(ZeroEvenOdd* obj, void(*printNumber)(int)) {
    for (int i = 1; i <= obj->n; i += 2) {
        printNumber(i);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    free(obj);
}

int main() {
    ZeroEvenOdd* obj = zeroEvenOddCreate(5);
    zeroEvenOddZero(obj, printNumber);
    zeroEvenOddEven(obj, printNumber);
    zeroEvenOddOdd(obj, printNumber);
    zeroEvenOddFree(obj);
    return 0;
}