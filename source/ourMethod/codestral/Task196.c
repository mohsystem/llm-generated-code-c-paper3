#include <stdio.h>
#include <pthread.h>

void printNumber(int num) {
    printf("%d", num);
}

int main() {
    int n = 5;
    ZeroEvenOdd zeroEvenOdd;
    ZeroEvenOdd_init(&zeroEvenOdd, n);

    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, (void*(*)(void*))ZeroEvenOdd_zero, &zeroEvenOdd);
    pthread_create(&threadB, NULL, (void*(*)(void*))ZeroEvenOdd_even, &zeroEvenOdd);
    pthread_create(&threadC, NULL, (void*(*)(void*))ZeroEvenOdd_odd, &zeroEvenOdd);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}