#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
    int zeroTurn;
} ZeroEvenOdd;

void* zero(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&obj->mtx);
        while (!obj->zeroTurn) {
            pthread_cond_wait(&obj->cv, &obj->mtx);
        }
        printf("0");
        obj->zeroTurn = 0;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->mtx);
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->zeroTurn || obj->current % 2 != 0) {
            pthread_cond_wait(&obj->cv, &obj->mtx);
        }
        printf("%d", obj->current++);
        obj->zeroTurn = 1;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->mtx);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->zeroTurn || obj->current % 2 == 0) {
            pthread_cond_wait(&obj->cv, &obj->mtx);
        }
        printf("%d", obj->current++);
        obj->zeroTurn = 1;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->mtx);
    }
    return NULL;
}

int main() {
    int testCases[] = {2, 3, 5, 6, 8};

    for (int i = 0; i < 5; ++i) {
        ZeroEvenOdd zeroEvenOdd;
        zeroEvenOdd.n = testCases[i];
        zeroEvenOdd.current = 1;
        zeroEvenOdd.zeroTurn = 1;
        pthread_mutex_init(&zeroEvenOdd.mtx, NULL);
        pthread_cond_init(&zeroEvenOdd.cv, NULL);

        pthread_t threadA, threadB, threadC;

        pthread_create(&threadA, NULL, zero, &zeroEvenOdd);
        pthread_create(&threadB, NULL, even, &zeroEvenOdd);
        pthread_create(&threadC, NULL, odd, &zeroEvenOdd);

        pthread_join(threadA, NULL);
        pthread_join(threadB, NULL);
        pthread_join(threadC, NULL);

        pthread_mutex_destroy(&zeroEvenOdd.mtx);
        pthread_cond_destroy(&zeroEvenOdd.cv);

        printf("\n");
    }

    return 0;
}