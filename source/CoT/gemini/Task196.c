#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// Define a structure to hold the shared data and semaphores
typedef struct {
    int n;
    sem_t zeroSem, evenSem, oddSem;
} ZeroEvenOdd;

// printNumber function (provided as a parameter)
void printNumber(int x) {
    printf("%d", x);
}

// Function for the "zero" thread
void* zero(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= zeo->n; i++) {
        sem_wait(&zeo->zeroSem);
        printNumber(0);
        if (i % 2 == 1) {
            sem_post(&zeo->oddSem);
        } else {
            sem_post(&zeo->evenSem);
        }
    }
    return NULL;
}

// Function for the "even" thread
void* even(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= zeo->n; i += 2) {
        sem_wait(&zeo->evenSem);
        printNumber(i);
        sem_post(&zeo->zeroSem);
    }
    return NULL;
}

// Function for the "odd" thread
void* odd(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;

    for (int i = 1; i <= zeo->n; i += 2) {
        sem_wait(&zeo->oddSem);
        printNumber(i);
        sem_post(&zeo->zeroSem);
    }
    return NULL;
}