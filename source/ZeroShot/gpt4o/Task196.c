#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zeroSem;
    sem_t evenSem;
    sem_t oddSem;
} ZeroEvenOdd;

void ZeroEvenOdd_init(ZeroEvenOdd* obj, int n) {
    obj->n = n;
    sem_init(&obj->zeroSem, 0, 1);
    sem_init(&obj->evenSem, 0, 0);
    sem_init(&obj->oddSem, 0, 0);
}

void* zero(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    for (int i = 0; i < obj->n; i++) {
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

void test_zero_even_odd(int n) {
    ZeroEvenOdd zeo;
    ZeroEvenOdd_init(&zeo, n);
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &zeo);
    pthread_create(&t2, NULL, even, &zeo);
    pthread_create(&t3, NULL, odd, &zeo);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
}

int main() {
    test_zero_even_odd(2);
    printf("\n");
    test_zero_even_odd(5);
    printf("\n");
    test_zero_even_odd(3);
    printf("\n");
    test_zero_even_odd(4);
    printf("\n");
    test_zero_even_odd(6);
    printf("\n");
    return 0;
}