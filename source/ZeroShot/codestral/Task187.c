#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

sem_t hydrogen;
sem_t oxygen;
sem_t barrier;

void *hydrogen_thread(void *arg) {
    sem_wait(&hydrogen);
    sem_wait(&barrier);
    printf("H");
    sem_post(&barrier);
    return NULL;
}

void *oxygen_thread(void *arg) {
    sem_wait(&oxygen);
    sem_wait(&barrier);
    printf("O");
    sem_post(&hydrogen);
    sem_post(&hydrogen);
    sem_post(&barrier);
    sem_post(&barrier);
    return NULL;
}

int main() {
    sem_init(&hydrogen, 0, 2);
    sem_init(&oxygen, 0, 0);
    sem_init(&barrier, 0, 3);

    pthread_t threads[6];
    for (int i = 0; i < 6; i++) {
        if (i % 3 == 2)
            pthread_create(&threads[i], NULL, oxygen_thread, NULL);
        else
            pthread_create(&threads[i], NULL, hydrogen_thread, NULL);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}