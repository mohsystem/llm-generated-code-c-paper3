#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool zero_turn;
} ZeroEvenOdd;

void printNumber(int number) {
    printf("%d", number);
}

void* zero(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 0; i < zeo->n; ++i) {
        pthread_mutex_lock(&zeo->mutex);
        while (!zeo->zero_turn) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(0);
        zeo->zero_turn = false;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= zeo->n; i += 2) {
        pthread_mutex_lock(&zeo->mutex);
        while (zeo->zero_turn || zeo->current % 2 != 0) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(i);
        zeo->current++;
        zeo->zero_turn = true;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= zeo->n; i += 2) {
        pthread_mutex_lock(&zeo->mutex);
        while (zeo->zero_turn || zeo->current % 2 == 0) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(i);
        zeo->current++;
        zeo->zero_turn = true;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void runTest(ZeroEvenOdd* zeo) {
    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, zero, zeo);
    pthread_create(&threadB, NULL, even, zeo);
    pthread_create(&threadC, NULL, odd, zeo);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
}

int main() {
    ZeroEvenOdd zeroEvenOdd1 = {2, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, true};
    ZeroEvenOdd zeroEvenOdd2 = {5, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, true};
    ZeroEvenOdd zeroEvenOdd3 = {10, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, true};
    ZeroEvenOdd zeroEvenOdd4 = {3, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, true};
    ZeroEvenOdd zeroEvenOdd5 = {1, 1, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, true};

    runTest(&zeroEvenOdd1);
    runTest(&zeroEvenOdd2);
    runTest(&zeroEvenOdd3);
    runTest(&zeroEvenOdd4);
    runTest(&zeroEvenOdd5);

    return 0;
}