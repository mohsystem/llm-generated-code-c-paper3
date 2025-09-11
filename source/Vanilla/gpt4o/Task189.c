#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zeroSem;
    sem_t oddSem;
    sem_t evenSem;
} ZeroEvenOdd;

void init(ZeroEvenOdd* obj, int n) {
    obj->n = n;
    sem_init(&obj->zeroSem, 0, 1);
    sem_init(&obj->oddSem, 0, 0);
    sem_init(&obj->evenSem, 0, 0);
}

void* zero(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 0; i < obj->n; ++i) {
        sem_wait(&obj->zeroSem);
        printf("0");
        if (i % 2 == 0) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        printf("%d", i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        printf("%d", i);
        sem_post(&obj->zeroSem);
    }
    return NULL;
}

int main() {
    ZeroEvenOdd instance1;
    init(&instance1, 2);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &instance1);
    pthread_create(&t2, NULL, even, &instance1);
    pthread_create(&t3, NULL, odd, &instance1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n");

    ZeroEvenOdd instance2;
    init(&instance2, 5);

    pthread_t t4, t5, t6;
    pthread_create(&t4, NULL, zero, &instance2);
    pthread_create(&t5, NULL, even, &instance2);
    pthread_create(&t6, NULL, odd, &instance2);

    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);

    printf("\n");

    return 0;
}