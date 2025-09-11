#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t hydrogenSemaphore;
sem_t oxygenSemaphore;
sem_t barrier;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* releaseHydrogen(void* arg) {
    sem_post(&hydrogenSemaphore);
    sem_wait(&barrier);
    pthread_mutex_lock(&lock);
    printf("H");
    pthread_mutex_unlock(&lock);
    sem_post(&barrier);
    return NULL;
}

void* releaseOxygen(void* arg) {
    sem_post(&oxygenSemaphore);
    sem_wait(&barrier);
    pthread_mutex_lock(&lock);
    printf("O");
    pthread_mutex_unlock(&lock);
    sem_post(&barrier);
    return NULL;
}

void waitBarrier() {
    for (int i = 0; i < 3; ++i) {
        sem_wait(&barrier);
        sem_post(&barrier);
    }
}

int main() {
    sem_init(&hydrogenSemaphore, 0, 2);
    sem_init(&oxygenSemaphore, 0, 1);
    sem_init(&barrier, 0, 0);

    char* water = "OOHHHH";
    int n = strlen(water) / 3;

    for (int i = 0; i < n; ++i) {
        if (water[i * 3] == 'O') {
            pthread_t t1, t2, t3;
            pthread_create(&t1, NULL, releaseOxygen, NULL);
            pthread_create(&t2, NULL, releaseHydrogen, NULL);
            pthread_create(&t3, NULL, releaseHydrogen, NULL);
            waitBarrier();
        } else {
            pthread_t t1, t2, t3;
            pthread_create(&t1, NULL, releaseHydrogen, NULL);
            pthread_create(&t2, NULL, releaseHydrogen, NULL);
            pthread_create(&t3, NULL, releaseOxygen, NULL);
            waitBarrier();
        }
    }

    return 0;
}