#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t hydrogenSemaphore;
sem_t oxygenSemaphore;

void* releaseHydrogen(void* arg) {
    sem_wait(&hydrogenSemaphore);
    printf("H");
    int val;
    sem_getvalue(&hydrogenSemaphore, &val);
    if (val == 0) {
        sem_post(&oxygenSemaphore);
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

void test_water(const char* water) {
    int len = strlen(water);
    pthread_t threads[len];
    
    for (int i = 0; i < len; i++) {
        if (water[i] == 'H') {
            pthread_create(&threads[i], NULL, releaseHydrogen, NULL);
        } else {
            pthread_create(&threads[i], NULL, releaseOxygen, NULL);
        }
    }

    for (int i = 0; i < len; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    sem_init(&hydrogenSemaphore, 0, 2);
    sem_init(&oxygenSemaphore, 0, 0);
    
    test_water("HOHOOHHHHHH");
    
    sem_destroy(&hydrogenSemaphore);
    sem_destroy(&oxygenSemaphore);
    
    return 0;
}