#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// Define the structure for ZeroEvenOdd
typedef struct {
    int n;
    sem_t zeroSem, evenSem, oddSem;
    int current;
    pthread_mutex_t printMutex;
} ZeroEvenOdd;

// Initialize the ZeroEvenOdd structure
void zeroEvenOddInit(ZeroEvenOdd* obj, int n) {
    obj->n = n;
    sem_init(&obj->zeroSem, 0, 1);
    sem_init(&obj->evenSem, 0, 0);
    sem_init(&obj->oddSem, 0, 0);
    obj->current = 1;
    pthread_mutex_init(&obj->printMutex, NULL);
}

// printNumber(x) outputs "x", where x is an integer.
void zero(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->zeroSem);
        pthread_mutex_lock(&obj->printMutex);
        printNumber(0);
        pthread_mutex_unlock(&obj->printMutex);

        if (obj->current % 2 == 1) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
}

void even(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        pthread_mutex_lock(&obj->printMutex);
        printNumber(i);
        pthread_mutex_unlock(&obj->printMutex);
        sem_post(&obj->zeroSem);
        obj->current++;
    }
}

void odd(ZeroEvenOdd* obj, void (*printNumber)(int)) {
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        pthread_mutex_lock(&obj->printMutex);
        printNumber(i);
        pthread_mutex_unlock(&obj->printMutex);
        sem_post(&obj->zeroSem);
        obj->current++;
    }
}

void printNumberC(int x) {
    printf("%d", x);
}

void test(int n) {
    ZeroEvenOdd zeo;
    zeroEvenOddInit(&zeo, n);
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, (void *(*)(void *))zero, &zeo);
    pthread_create(&t2, NULL, (void *(*)(void *))even, &zeo);
    pthread_create(&t3, NULL, (void *(*)(void *))odd, &zeo);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    printf("\n");
}

int main() {
    test(2);
    test(5);
    test(1);
    test(3);
    test(10);
    return 0;
}