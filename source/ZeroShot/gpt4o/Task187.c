#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t hydrogenSemaphore;
    sem_t oxygenSemaphore;
    int hydrogenCount;
    int oxygenCount;
    pthread_mutex_t mutex;
} Task187;

void* releaseHydrogen(void* arg) {
    Task187* task = (Task187*)arg;
    sem_wait(&task->hydrogenSemaphore);
    pthread_mutex_lock(&task->mutex);
    printf("H");
    task->hydrogenCount++;
    if (task->hydrogenCount == 2 && task->oxygenCount == 1) {
        task->hydrogenCount = 0;
        task->oxygenCount = 0;
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->oxygenSemaphore);
    }
    pthread_mutex_unlock(&task->mutex);
    return NULL;
}

void* releaseOxygen(void* arg) {
    Task187* task = (Task187*)arg;
    sem_wait(&task->oxygenSemaphore);
    pthread_mutex_lock(&task->mutex);
    printf("O");
    task->oxygenCount++;
    if (task->hydrogenCount == 2 && task->oxygenCount == 1) {
        task->hydrogenCount = 0;
        task->oxygenCount = 0;
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->oxygenSemaphore);
    }
    pthread_mutex_unlock(&task->mutex);
    return NULL;
}

int main() {
    Task187 task;
    sem_init(&task.hydrogenSemaphore, 0, 2);
    sem_init(&task.oxygenSemaphore, 0, 1);
    pthread_mutex_init(&task.mutex, NULL);

    char water[] = "HOHHOHHOHHOH";
    pthread_t threads[12];
    int threadIndex = 0;

    for (int i = 0; i < 12; i++) {
        if (water[i] == 'H') {
            pthread_create(&threads[threadIndex++], NULL, releaseHydrogen, &task);
        } else {
            pthread_create(&threads[threadIndex++], NULL, releaseOxygen, &task);
        }
    }

    for (int i = 0; i < 12; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&task.hydrogenSemaphore);
    sem_destroy(&task.oxygenSemaphore);
    pthread_mutex_destroy(&task.mutex);

    return 0;
}