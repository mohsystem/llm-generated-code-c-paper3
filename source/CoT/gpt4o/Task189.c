#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zeroSemaphore;
    sem_t oddSemaphore;
    sem_t evenSemaphore;
} ZeroEvenOdd;

void ZeroEvenOdd_init(ZeroEvenOdd* obj, int n) {
    obj->n = n;
    sem_init(&obj->zeroSemaphore, 0, 1);
    sem_init(&obj->oddSemaphore, 0, 0);
    sem_init(&obj->evenSemaphore, 0, 0);
}

void* zero(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 0; i < obj->n; ++i) {
        sem_wait(&obj->zeroSemaphore);
        printf("%d", 0);
        if (i % 2 == 0) {
            sem_post(&obj->oddSemaphore);
        } else {
            sem_post(&obj->evenSemaphore);
        }
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSemaphore);
        printf("%d", i);
        sem_post(&obj->zeroSemaphore);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSemaphore);
        printf("%d", i);
        sem_post(&obj->zeroSemaphore);
    }
    return NULL;
}

int main() {
    ZeroEvenOdd instance;
    ZeroEvenOdd_init(&instance, 5);

    pthread_t threadA, threadB, threadC;
    pthread_create(&threadA, NULL, zero, &instance);
    pthread_create(&threadB, NULL, even, &instance);
    pthread_create(&threadC, NULL, odd, &instance);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}