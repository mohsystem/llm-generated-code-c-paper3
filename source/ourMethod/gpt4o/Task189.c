#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zeroSem, oddSem, evenSem;
} ZeroEvenOdd;

void initZeroEvenOdd(ZeroEvenOdd *obj, int n) {
    obj->n = n;
    sem_init(&obj->zeroSem, 0, 1);
    sem_init(&obj->oddSem, 0, 0);
    sem_init(&obj->evenSem, 0, 0);
}

void printNumber(int x) {
    printf("%d", x);
}

void *zero(void *arg) {
    ZeroEvenOdd *obj = (ZeroEvenOdd *)arg;
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->zeroSem);
        printNumber(0);
        if (i % 2 == 0) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
    return NULL;
}

void *even(void *arg) {
    ZeroEvenOdd *obj = (ZeroEvenOdd *)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        printNumber(i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

void *odd(void *arg) {
    ZeroEvenOdd *obj = (ZeroEvenOdd *)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        printNumber(i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

int main() {
    ZeroEvenOdd obj;
    initZeroEvenOdd(&obj, 5);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &obj);
    pthread_create(&t2, NULL, even, &obj);
    pthread_create(&t3, NULL, odd, &obj);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}