#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zero_sem;
    sem_t even_sem;
    sem_t odd_sem;
} ZeroEvenOdd;

void printNumber(int x) {
    printf("%d", x);
}

void* zero(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*) arg;
    for (int i = 1; i <= zeo->n; i++) {
        sem_wait(&zeo->zero_sem);
        printNumber(0);
        if (i % 2 == 1) {
            sem_post(&zeo->odd_sem);
        } else {
            sem_post(&zeo->even_sem);
        }
    }
    return NULL;
}

void* even(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*) arg;
    for (int i = 2; i <= zeo->n; i += 2) {
        sem_wait(&zeo->even_sem);
        printNumber(i);
        sem_post(&zeo->zero_sem);
    }
    return NULL;
}

void* odd(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*) arg;
    for (int i = 1; i <= zeo->n; i += 2) {
        sem_wait(&zeo->odd_sem);
        printNumber(i);
        sem_post(&zeo->zero_sem);
    }
    return NULL;
}

int main() {
    void test(int n) {
        ZeroEvenOdd zeo;
        zeo.n = n;
        sem_init(&zeo.zero_sem, 0, 1);
        sem_init(&zeo.even_sem, 0, 0);
        sem_init(&zeo.odd_sem, 0, 0);

        pthread_t t1, t2, t3;
        pthread_create(&t1, NULL, zero, &zeo);
        pthread_create(&t2, NULL, even, &zeo);
        pthread_create(&t3, NULL, odd, &zeo);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);

        sem_destroy(&zeo.zero_sem);
        sem_destroy(&zeo.even_sem);
        sem_destroy(&zeo.odd_sem);
        printf("\n");
    }

    test(2);
    test(5);
    test(1);
    test(3);
    test(4);
    return 0;
}