#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int zero_turn;
} ZeroEvenOdd;

void printNumber(int x) {
    printf("%d", x);
}

void* zero(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&obj->mutex);
        while (!obj->zero_turn) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(0);
        obj->zero_turn = 0;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->zero_turn || obj->count % 2 != 0) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(obj->count++);
        obj->zero_turn = 1;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->zero_turn || obj->count % 2 == 0) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(obj->count++);
        obj->zero_turn = 1;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
    return NULL;
}

void runTest(int n) {
    ZeroEvenOdd zeroEvenOdd;
    zeroEvenOdd.n = n;
    zeroEvenOdd.count = 1;
    zeroEvenOdd.zero_turn = 1;
    pthread_mutex_init(&zeroEvenOdd.mutex, NULL);
    pthread_cond_init(&zeroEvenOdd.cond, NULL);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &zeroEvenOdd);
    pthread_create(&t2, NULL, even, &zeroEvenOdd);
    pthread_create(&t3, NULL, odd, &zeroEvenOdd);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n");

    pthread_mutex_destroy(&zeroEvenOdd.mutex);
    pthread_cond_destroy(&zeroEvenOdd.cond);
}

int main() {
    runTest(2);
    runTest(5);
    runTest(1);
    runTest(10);
    runTest(3);
    return 0;
}