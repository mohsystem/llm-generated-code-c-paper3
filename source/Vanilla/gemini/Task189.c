#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef void (*printNumber)(int);

typedef struct {
    int n;
    int current;
    sem_t zeroSem, evenSem, oddSem;
} ZeroEvenOdd;

void zero(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->zeroSem);
        printNumber(0);
        if (obj->current % 2 == 1) {
            sem_post(&obj->oddSem);
        } else {
            sem_post(&obj->evenSem);
        }
    }
}

void even(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 2; i <= obj->n; i += 2) {
        sem_wait(&obj->evenSem);
        printNumber(i);
        obj->current++;
        sem_post(&obj->zeroSem);
    }
}

void odd(ZeroEvenOdd* obj, printNumber printNumber) {
    for (int i = 1; i <= obj->n; i += 2) {
        sem_wait(&obj->oddSem);
        printNumber(i);
        obj->current++;
        sem_post(&obj->zeroSem);
    }
}


void* zero_thread(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
    void (*printNum)(int) = (printNumber) ((void**)arg)[1];
    zero(obj, printNum);
    return NULL;
}
void* even_thread(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
     void (*printNum)(int) = (printNumber) ((void**)arg)[1];
    even(obj, printNum);
    return NULL;
}
void* odd_thread(void* arg) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)arg;
     void (*printNum)(int) = (printNumber) ((void**)arg)[1];
    odd(obj, printNum);
    return NULL;
}


void test(int n) {
    ZeroEvenOdd obj;
    obj.n = n;
    obj.current = 1;
    sem_init(&obj.zeroSem, 0, 1);
    sem_init(&obj.evenSem, 0, 0);
    sem_init(&obj.oddSem, 0, 0);

    char output[2001] = {0};
    int output_index = 0;
    void printNum(int x) {
        output[output_index++] = x + '0';
    }

    pthread_t t1, t2, t3;
    void *args[2] = {&obj, printNum};
    pthread_create(&t1, NULL, zero_thread, args);
    pthread_create(&t2, NULL, even_thread, args);
    pthread_create(&t3, NULL, odd_thread, args);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("n = %d, Output: %s\n", n, output);

    sem_destroy(&obj.zeroSem);
    sem_destroy(&obj.evenSem);
    sem_destroy(&obj.oddSem);
}

int main() {
    test(2);
    test(5);
    test(1);
    test(3);
    test(4);
    return 0;
}