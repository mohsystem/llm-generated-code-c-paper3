#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int currentCounter;
    int maxCounter;
    pthread_mutex_t lock;
} Task92;

void* incrementCounter(void* arg) {
    Task92* task = (Task92*)arg;
    char threadName[20];
    snprintf(threadName, sizeof(threadName), "Thread-%lu", pthread_self());

    while (1) {
        pthread_mutex_lock(&task->lock);
        if (task->currentCounter > task->maxCounter) {
            pthread_mutex_unlock(&task->lock);
            break;
        }
        task->currentCounter++;
        printf("%s is accessing currentCounter: %d\n", threadName, task->currentCounter);
        pthread_mutex_unlock(&task->lock);

        usleep(100000); // simulate some work
    }
    return NULL;
}

int main() {
    Task92 task;
    task.currentCounter = 0;
    task.maxCounter = 10;
    pthread_mutex_init(&task.lock, NULL);

    pthread_t threads[5];
    for (int i = 0; i < 5; ++i) {
        pthread_create(&threads[i], NULL, incrementCounter, (void*)&task);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&task.lock);
    return 0;
}