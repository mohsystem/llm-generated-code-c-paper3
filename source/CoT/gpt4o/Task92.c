#include <stdio.h>
#include <pthread.h>

typedef struct {
    int currentCounter;
    int maxCounter;
    pthread_mutex_t lock;
} Task92;

void initTask(Task92 *task, int maxCounter) {
    task->currentCounter = 0;
    task->maxCounter = maxCounter;
    pthread_mutex_init(&task->lock, NULL);
}

void* accessResource(void* arg) {
    Task92* task = (Task92*)arg;
    char threadName[16];
    sprintf(threadName, "Thread-%lu", pthread_self());

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&task->lock);
        if (task->currentCounter <= task->maxCounter) {
            printf("%s accessing currentCounter: %d\n", threadName, task->currentCounter);
            task->currentCounter++;
        }
        pthread_mutex_unlock(&task->lock);
    }
    return NULL;
}

int main() {
    Task92 task;
    initTask(&task, 10);

    pthread_t threads[5];

    for (int i = 0; i < 5; ++i) {
        pthread_create(&threads[i], NULL, accessResource, &task);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&task.lock);
    return 0;
}