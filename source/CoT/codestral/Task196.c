// C does not support multithreading in the same way as Java, CPP, and Python.
// Therefore, a direct translation of the Java solution to C is not possible.
// However, the logic can be implemented using POSIX threads (pthreads) and mutexes.
// This is a simplified version without actual multithreading.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef void (*printNumber_t)(int);

typedef struct {
    int n;
    sem_t zero_sem;
    sem_t even_sem;
    sem_t odd_sem;
    printNumber_t printNumber;
} ZeroEvenOdd;

void zero(ZeroEvenOdd* obj) {
    for (int i = 0; i < obj->n; ++i) {
        sem_wait(&obj->zero_sem);
        obj->printNumber(0);
        if (i % 2 == 0) {
            sem_post(&obj->odd_sem);
        } else {
            sem_post(&obj->even_sem);
        }
    }
}

void even(ZeroEvenOdd* obj) {
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->even_sem);
        obj->printNumber(i);
        sem_post(&obj->zero_sem);
    }
}

void odd(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->odd_sem);
        obj->printNumber(i);
        sem_post(&obj->zero_sem);
    }
}

void ZeroEvenOdd_init(ZeroEvenOdd* obj, int n, printNumber_t printNumber) {
    obj->n = n;
    sem_init(&obj->zero_sem, 0, 1);
    sem_init(&obj->even_sem, 0, 0);
    sem_init(&obj->odd_sem, 0, 0);
    obj->printNumber = printNumber;
}

void printNumberImpl(int num) {
    printf("%d", num);
}

int main() {
    ZeroEvenOdd obj;
    ZeroEvenOdd_init(&obj, 5, printNumberImpl);

    pthread_t thread_zero, thread_even, thread_odd;
    pthread_create(&thread_zero, NULL, (void*)zero, &obj);
    pthread_create(&thread_even, NULL, (void*)even, &obj);
    pthread_create(&thread_odd, NULL, (void*)odd, &obj);

    pthread_join(thread_zero, NULL);
    pthread_join(thread_even, NULL);
    pthread_join(thread_odd, NULL);

    return 0;
}