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

void init(Task187 *task) {
    sem_init(&task->hydrogenSemaphore, 0, 2);
    sem_init(&task->oxygenSemaphore, 0, 1);
    task->hydrogenCount = 0;
    task->oxygenCount = 0;
    pthread_mutex_init(&task->mutex, NULL);
}

void releaseHydrogen(Task187 *task) {
    sem_wait(&task->hydrogenSemaphore);
    printf("H");
    pthread_mutex_lock(&task->mutex);
    if (++task->hydrogenCount == 2) {
        task->hydrogenCount = 0;
        sem_post(&task->oxygenSemaphore);
    }
    pthread_mutex_unlock(&task->mutex);
}

void releaseOxygen(Task187 *task) {
    sem_wait(&task->oxygenSemaphore);
    printf("O");
    pthread_mutex_lock(&task->mutex);
    if (++task->oxygenCount == 1) {
        task->oxygenCount = 0;
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->hydrogenSemaphore);
    }
    pthread_mutex_unlock(&task->mutex);
}

void* hydrogen_thread(void* arg) {
    releaseHydrogen((Task187*)arg);
    return NULL;
}

void* oxygen_thread(void* arg) {
    releaseOxygen((Task187*)arg);
    return NULL;
}

int main() {
    Task187 task;
    init(&task);
    char water[] = "OOHHHH";
    pthread_t threads[6];

    for (int i = 0; i < 6; i++) {
        if (water[i] == 'H') {
            pthread_create(&threads[i], NULL, hydrogen_thread, (void*)&task);
        } else {
            pthread_create(&threads[i], NULL, oxygen_thread, (void*)&task);
        }
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}