// Note: Implementing threads and synchronization in C is more complex and typically involves POSIX threads.
// Here is a simplified version without proper synchronization.

#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mutex;
    pthread_cond_t zeroCond;
    pthread_cond_t evenCond;
    pthread_cond_t oddCond;
    int zeroTurn;
    int evenTurn;
    int oddTurn;
} ZeroEvenOdd;

void* zero(void* arg) {
    ZeroEvenOdd* zeroEvenOdd = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= zeroEvenOdd->n; ++i) {
        pthread_mutex_lock(&zeroEvenOdd->mutex);
        while (!zeroEvenOdd->zeroTurn) {
            pthread_cond_wait(&zeroEvenOdd->zeroCond, &zeroEvenOdd->mutex);
        }
        printf("0");
        if (i % 2 == 1) {
            zeroEvenOdd->oddTurn = 1;
            zeroEvenOdd->zeroTurn = 0;
        } else {
            zeroEvenOdd->evenTurn = 1;
            zeroEvenOdd->zeroTurn = 0;
        }
        pthread_cond_signal(zeroEvenOdd->evenTurn ? &zeroEvenOdd->evenCond : &zeroEvenOdd->oddCond);
        pthread_mutex_unlock(&zeroEvenOdd->mutex);
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* zeroEvenOdd = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= zeroEvenOdd->n; i += 2) {
        pthread_mutex_lock(&zeroEvenOdd->mutex);
        while (!zeroEvenOdd->evenTurn) {
            pthread_cond_wait(&zeroEvenOdd->evenCond, &zeroEvenOdd->mutex);
        }
        printf("%d", i);
        zeroEvenOdd->zeroTurn = 1;
        zeroEvenOdd->evenTurn = 0;
        pthread_cond_signal(&zeroEvenOdd->zeroCond);
        pthread_mutex_unlock(&zeroEvenOdd->mutex);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* zeroEvenOdd = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= zeroEvenOdd->n; i += 2) {
        pthread_mutex_lock(&zeroEvenOdd->mutex);
        while (!zeroEvenOdd->oddTurn) {
            pthread_cond_wait(&zeroEvenOdd->oddCond, &zeroEvenOdd->mutex);
        }
        printf("%d", i);
        zeroEvenOdd->zeroTurn = 1;
        zeroEvenOdd->oddTurn = 0;
        pthread_cond_signal(&zeroEvenOdd->zeroCond);
        pthread_mutex_unlock(&zeroEvenOdd->mutex);
    }
    return NULL;
}

int main() {
    ZeroEvenOdd zeroEvenOdd;
    zeroEvenOdd.n = 5;
    zeroEvenOdd.current = 0;
    zeroEvenOdd.zeroTurn = 1;
    zeroEvenOdd.evenTurn = 0;
    zeroEvenOdd.oddTurn = 0;

    pthread_mutex_init(&zeroEvenOdd.mutex, NULL);
    pthread_cond_init(&zeroEvenOdd.zeroCond, NULL);
    pthread_cond_init(&zeroEvenOdd.evenCond, NULL);
    pthread_cond_init(&zeroEvenOdd.oddCond, NULL);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &zeroEvenOdd);
    pthread_create(&t2, NULL, even, &zeroEvenOdd);
    pthread_create(&t3, NULL, odd, &zeroEvenOdd);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&zeroEvenOdd.mutex);
    pthread_cond_destroy(&zeroEvenOdd.zeroCond);
    pthread_cond_destroy(&zeroEvenOdd.evenCond);
    pthread_cond_destroy(&zeroEvenOdd.oddCond);

    return 0;
}