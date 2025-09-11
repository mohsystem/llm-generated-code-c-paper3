#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    sem_t oxygenSemaphore;
    sem_t hydrogenSemaphore;
    int hydrogenCount;
    pthread_mutex_t lock;
} Task187;

void initTask187(Task187* task) {
    sem_init(&task->oxygenSemaphore, 0, 0);
    sem_init(&task->hydrogenSemaphore, 0, 0);
    task->hydrogenCount = 0;
    pthread_mutex_init(&task->lock, NULL);
}

void destroyTask187(Task187* task) {
    sem_destroy(&task->oxygenSemaphore);
    sem_destroy(&task->hydrogenSemaphore);
    pthread_mutex_destroy(&task->lock);
}

void releaseHydrogen(Task187* task) {
    pthread_mutex_lock(&task->lock);
    task->hydrogenCount++;
    if (task->hydrogenCount == 2) {
        sem_post(&task->oxygenSemaphore);
        sem_post(&task->hydrogenSemaphore);
        sem_post(&task->hydrogenSemaphore);
        task->hydrogenCount = 0;
    }
    pthread_mutex_unlock(&task->lock);
    sem_wait(&task->hydrogenSemaphore);
    printf("H");
}

void releaseOxygen(Task187* task) {
    sem_wait(&task->oxygenSemaphore);
    printf("O");
}

void* hydrogenThread(void* arg) {
    Task187* task = (Task187*)arg;
    releaseHydrogen(task);
    return NULL;
}

void* oxygenThread(void* arg) {
    Task187* task = (Task187*)arg;
    releaseOxygen(task);
    return NULL;
}

int main() {
    Task187 task;
    initTask187(&task);

    // Test cases
    for (char c : "HOH") {
        if (c == 'H') {
            pthread_t thread;
            pthread_create(&thread, NULL, hydrogenThread, &task);
            pthread_detach(thread);
        } else {
            pthread_t thread;
            pthread_create(&thread, NULL, oxygenThread, &task);
            pthread_detach(thread);
        }
    }

    for (char c : "OOHHHH") {
        if (c == 'H') {
            pthread_t thread;
            pthread_create(&thread, NULL, hydrogenThread, &task);
            pthread_detach(thread);
        } else {
            pthread_t thread;
            pthread_create(&thread, NULL, oxygenThread, &task);
            pthread_detach(thread);
        }
    }

    destroyTask187(&task);
    return 0;
}