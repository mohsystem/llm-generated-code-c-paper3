#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t zeroSem, evenSem, oddSem;

void* zero(void* arg) {
    int n = *(int*)arg;
    for (int i = 1; i <= n; ++i) {
        sem_wait(&zeroSem);
        printf("0");
        if (i % 2 == 1) {
            sem_post(&oddSem);
        } else {
            sem_post(&evenSem);
        }
    }
    return NULL;
}

void* even(void* arg) {
    int n = *(int*)arg;
    for (int i = 2; i <= n; i += 2) {
        sem_wait(&evenSem);
        printf("%d", i);
        sem_post(&zeroSem);
    }
    return NULL;
}

void* odd(void* arg) {
    int n = *(int*)arg;
    for (int i = 1; i <= n; i += 2) {
        sem_wait(&oddSem);
        printf("%d", i);
        sem_post(&zeroSem);
    }
    return NULL;
}

int main() {
    int n = 5;
    sem_init(&zeroSem, 0, 1);
    sem_init(&evenSem, 0, 0);
    sem_init(&oddSem, 0, 0);

    pthread_t threadA, threadB, threadC;
    pthread_create(&threadA, NULL, zero, &n);
    pthread_create(&threadB, NULL, even, &n);
    pthread_create(&threadC, NULL, odd, &n);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    sem_destroy(&zeroSem);
    sem_destroy(&evenSem);
    sem_destroy(&oddSem);

    return 0;
}