#include <semaphore.h>
#include <pthread.h>

typedef void (*releaseFunc)();

typedef struct {
    sem_t hydrogenSemaphore;
    sem_t oxygenSemaphore;
} H2O;

H2O* H2O_create() {
    H2O* h2o = malloc(sizeof(H2O));
    sem_init(&h2o->hydrogenSemaphore, 0, 2);
    sem_init(&h2o->oxygenSemaphore, 0, 0);
    return h2o;
}

void hydrogen(H2O* h2o, releaseFunc releaseHydrogen) {
    sem_wait(&h2o->hydrogenSemaphore);
    releaseHydrogen();
    sem_post(&h2o->oxygenSemaphore);
}

void oxygen(H2O* h2o, releaseFunc releaseOxygen) {
    sem_wait(&h2o->oxygenSemaphore);
    sem_wait(&h2o->oxygenSemaphore);
    releaseOxygen();
    sem_post(&h2o->hydrogenSemaphore);
    sem_post(&h2o->hydrogenSemaphore);
}