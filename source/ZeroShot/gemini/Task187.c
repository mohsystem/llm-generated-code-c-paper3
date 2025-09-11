#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t hydrogen_sem;
    sem_t oxygen_sem;
    int hydrogen_count;
    int oxygen_count;
    pthread_mutex_t mutex;
} H2O;

void* releaseHydrogen(void* arg) {
    H2O* water = (H2O*) arg;
    pthread_mutex_lock(&water->mutex);
    water->hydrogen_count++;
    if (water->hydrogen_count >= 2 && water->oxygen_count >= 1) {
        sem_post(&water->hydrogen_sem);
        sem_post(&water->hydrogen_sem);
        sem_post(&water->oxygen_sem);
        water->hydrogen_count -= 2;
        water->oxygen_count--;
    }
    pthread_mutex_unlock(&water->mutex);
    sem_wait(&water->hydrogen_sem);
    printf("H");
    return NULL;
}

void* releaseOxygen(void* arg) {
    H2O* water = (H2O*) arg;
    pthread_mutex_lock(&water->mutex);
    water->oxygen_count++;
    if (water->hydrogen_count >= 2 && water->oxygen_count >= 1) {
        sem_post(&water->hydrogen_sem);
        sem_post(&water->hydrogen_sem);
        sem_post(&water->oxygen_sem);
        water->hydrogen_count -= 2;
        water->oxygen_count--;
    }
    pthread_mutex_unlock(&water->mutex);

    sem_wait(&water->oxygen_sem);
    printf("O");
    return NULL;
}

int main() {
    H2O water;
    sem_init(&water.hydrogen_sem, 0, 0);
    sem_init(&water.oxygen_sem, 0, 0);
    water.hydrogen_count = 0;
    water.oxygen_count = 0;
    pthread_mutex_init(&water.mutex, NULL);


    char* testCases[] = {"HOH", "OOHHHH", "HOHHOH", "OHHHHO", "HHOOHH"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char* testCase = testCases[i];
        int len = strlen(testCase);
        pthread_t threads[len];

        for (int j = 0; j < len; j++) {
            if (testCase[j] == 'H') {
                pthread_create(&threads[j], NULL, releaseHydrogen, &water);
            } else {
                pthread_create(&threads[j], NULL, releaseOxygen, &water);
            }
        }

        for (int j = 0; j < len; j++) {
            pthread_join(threads[j], NULL);
        }
        printf("\n");
    }

        sem_destroy(&water.hydrogen_sem);
        sem_destroy(&water.oxygen_sem);
        pthread_mutex_destroy(&water.mutex);
    return 0;
}