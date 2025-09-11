#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zeroSem, oddSem, evenSem;
} Task196;

void* zero(void* arg) {
    Task196* obj = (Task196*)arg;
    for (int i = 0; i < obj->n; ++i) {
        sem_wait(&obj->zeroSem);
        printf("%d", 0);
        if (i % 2 == 0) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
    return NULL;
}

void* even(void* arg) {
    Task196* obj = (Task196*)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        printf("%d", i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

void* odd(void* arg) {
    Task196* obj = (Task196*)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        printf("%d", i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

int main() {
    Task196 zeroEvenOdd;
    zeroEvenOdd.n = 5;
    sem_init(&zeroEvenOdd.zeroSem, 0, 1);
    sem_init(&zeroEvenOdd.oddSem, 0, 0);
    sem_init(&zeroEvenOdd.evenSem, 0, 0);

    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, zero, &zeroEvenOdd);
    pthread_create(&threadB, NULL, even, &zeroEvenOdd);
    pthread_create(&threadC, NULL, odd, &zeroEvenOdd);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}