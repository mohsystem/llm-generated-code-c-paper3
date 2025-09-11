#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t hydrogen;
    sem_t oxygen;
    pthread_mutex_t mutex;
} H2O;

void* hydrogen(void* arg) {
    H2O* h2o = (H2O*)arg;
    sem_wait(&h2o->hydrogen);
    pthread_mutex_lock(&h2o->mutex);
    printf("H");
    if (sem_trywait(&h2o->hydrogen) == -1) {
        sem_post(&h2o->oxygen);
    }
    pthread_mutex_unlock(&h2o->mutex);
    return NULL;
}

void* oxygen(void* arg) {
    H2O* h2o = (H2O*)arg;
    sem_wait(&h2o->oxygen);
    pthread_mutex_lock(&h2o->mutex);
    printf("O");
    sem_post(&h2o->hydrogen);
    sem_post(&h2o->hydrogen);
    pthread_mutex_unlock(&h2o->mutex);
    return NULL;
}

int main() {
    H2O h2o;
    sem_init(&h2o.hydrogen, 0, 2);
    sem_init(&h2o.oxygen, 0, 0);
    pthread_mutex_init(&h2o.mutex, NULL);

    // Test cases
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, hydrogen, &h2o);
    pthread_create(&t2, NULL, hydrogen, &h2o);
    pthread_create(&t3, NULL, oxygen, &h2o);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&h2o.hydrogen);
    sem_destroy(&h2o.oxygen);
    pthread_mutex_destroy(&h2o.mutex);

    return 0;
}