#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    sem_t zeroSem;
    sem_t evenSem;
    sem_t oddSem;
} Task189;

void* zero(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 1; i <= task->n; ++i) {
        sem_wait(&task->zeroSem);
        printf("0");
        if (i % 2 == 0) {
            sem_post(&task->evenSem);
        } else {
            sem_post(&task->oddSem);
        }
    }
    return NULL;
}

void* even(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 2; i <= task->n; i += 2) {
        sem_wait(&task->evenSem);
        printf("%d", i);
        sem_post(&task->zeroSem);
    }
    return NULL;
}

void* odd(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 1; i <= task->n; i += 2) {
        sem_wait(&task->oddSem);
        printf("%d", i);
        sem_post(&task->zeroSem);
    }
    return NULL;
}

int main() {
    Task189 task;
    task.n = 5;
    sem_init(&task.zeroSem, 0, 1);
    sem_init(&task.evenSem, 0, 0);
    sem_init(&task.oddSem, 0, 0);

    pthread_t threadA, threadB, threadC;
    pthread_create(&threadA, NULL, zero, &task);
    pthread_create(&threadB, NULL, even, &task);
    pthread_create(&threadC, NULL, odd, &task);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    sem_destroy(&task.zeroSem);
    sem_destroy(&task.evenSem);
    sem_destroy(&task.oddSem);

    return 0;
}