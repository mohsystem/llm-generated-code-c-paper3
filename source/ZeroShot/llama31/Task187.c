#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t hydrogenSemaphore;
sem_t oxygenSemaphore;
int hydrogenCount = 0;

void* releaseHydrogen(void* arg) {
    sem_wait(&hydrogenSemaphore);
    printf("H");
    hydrogenCount++;
    if (hydrogenCount == 2) {
        sem_post(&oxygenSemaphore);
        sem_post(&hydrogenSemaphore);
        sem_post(&hydrogenSemaphore);
        hydrogenCount = 0;
    }
    return NULL;
}

void* releaseOxygen(void* arg) {
    sem_wait(&oxygenSemaphore);
    printf("O");
    sem_post(&hydrogenSemaphore);
    sem_post(&hydrogenSemaphore);
    return NULL;
}

int main() {
    sem_init(&hydrogenSemaphore, 0, 0);
    sem_init(&oxygenSemaphore, 0, 0);

    char water[] = "HOH";
    pthread_t threads[3];
    for (int i = 0; i < strlen(water); i++) {
        if (water[i] == 'H') {
            pthread_create(&threads[i], NULL, releaseHydrogen, NULL);
        } else {
            pthread_create(&threads[i], NULL, releaseOxygen, NULL);
        }
    }

    for (int i = 0; i < strlen(water); i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&hydrogenSemaphore);
    sem_destroy(&oxygenSemaphore);

    return 0;
}