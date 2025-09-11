#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t hydrogen_cv;
pthread_cond_t oxygen_cv;
int hydrogen_count = 0;

void releaseHydrogen() {
    printf("H");
}

void releaseOxygen() {
    printf("O");
}

void* hydrogen(void* arg) {
    pthread_mutex_lock(&mutex);
    while (hydrogen_count >= 2) {
        pthread_cond_wait(&hydrogen_cv, &mutex);
    }
    releaseHydrogen();
    hydrogen_count++;
    if (hydrogen_count == 2) {
        pthread_cond_signal(&oxygen_cv);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* oxygen(void* arg) {
    pthread_mutex_lock(&mutex);
    while (hydrogen_count < 2) {
        pthread_cond_wait(&oxygen_cv, &mutex);
    }
    releaseOxygen();
    hydrogen_count = 0;
    pthread_cond_broadcast(&hydrogen_cv);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[6];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&hydrogen_cv, NULL);
    pthread_cond_init(&oxygen_cv, NULL);

    // Test case 1: HHO
    pthread_create(&threads[0], NULL, hydrogen, NULL);
    pthread_create(&threads[1], NULL, hydrogen, NULL);
    pthread_create(&threads[2], NULL, oxygen, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n");

    // Test case 2: HHOHHO
    pthread_create(&threads[3], NULL, hydrogen, NULL);
    pthread_create(&threads[4], NULL, hydrogen, NULL);
    pthread_create(&threads[5], NULL, oxygen, NULL);

    for (int i = 3; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&hydrogen_cv);
    pthread_cond_destroy(&oxygen_cv);

    return 0;
}