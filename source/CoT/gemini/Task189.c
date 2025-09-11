#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Define the printNumber function pointer type
typedef void (*printNumber)(int);


typedef struct {
    int n;
    int current;
    sem_t zero_sem, even_sem, odd_sem;
} ZeroEvenOdd;

void* zero(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    printNumber print = (printNumber)zeo->zero_sem.__align; // Retrieve printNumber from semaphore
    for (int i = 0; i < zeo->n; i++) {
        sem_wait(&zeo->zero_sem);
        print(0);
        if (zeo->current % 2 == 1) {
            sem_post(&zeo->odd_sem);
        } else {
            sem_post(&zeo->even_sem);
        }
    }
    return NULL;
}


void* even(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
     printNumber print = (printNumber)zeo->zero_sem.__align; // Retrieve printNumber from semaphore

    for (int i = 2; i <= zeo->n; i += 2) {
        sem_wait(&zeo->even_sem);
        print(i);
        zeo->current++;
        sem_post(&zeo->zero_sem);
    }

    return NULL;

}

void* odd(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
     printNumber print = (printNumber)zeo->zero_sem.__align; // Retrieve printNumber from semaphore
    for (int i = 1; i <= zeo->n; i += 2) {
        sem_wait(&zeo->odd_sem);
        print(i);
        zeo->current++;
        sem_post(&zeo->zero_sem);
    }
    return NULL;
}

void test(int n, printNumber print) {
    ZeroEvenOdd zeo;
    zeo.n = n;
    zeo.current = 1;

    // Store printNumber in zero_sem for retrieval in thread functions
    zeo.zero_sem.__align = print;

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

void printNumberToConsole(int x) {
    printf("%d", x);
}

int main() {
    test(2, printNumberToConsole);
    test(5, printNumberToConsole);
    test(1, printNumberToConsole);
    test(10, printNumberToConsole);
    test(3, printNumberToConsole);
    return 0;
}