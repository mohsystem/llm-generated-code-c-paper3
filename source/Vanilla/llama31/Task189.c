#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Task189;

void* zero(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 1; i <= task->n; ++i) {
        pthread_mutex_lock(&task->mutex);
        while (task->current != 1) {
            pthread_cond_wait(&task->cond, &task->mutex);
        }
        printf("0");
        task->current = (i % 2 == 0) ? 2 : 3;
        pthread_cond_broadcast(&task->cond);
        pthread_mutex_unlock(&task->mutex);
    }
    return NULL;
}

void* even(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 2; i <= task->n; i += 2) {
        pthread_mutex_lock(&task->mutex);
        while (task->current != 2) {
            pthread_cond_wait(&task->cond, &task->mutex);
        }
        printf("%d", i);
        task->current = 1;
        pthread_cond_broadcast(&task->cond);
        pthread_mutex_unlock(&task->mutex);
    }
    return NULL;
}

void* odd(void* arg) {
    Task189* task = (Task189*)arg;
    for (int i = 1; i <= task->n; i += 2) {
        pthread_mutex_lock(&task->mutex);
        while (task->current != 3) {
            pthread_cond_wait(&task->cond, &task->mutex);
        }
        printf("%d", i);
        task->current = 1;
        pthread_cond_broadcast(&task->cond);
        pthread_mutex_unlock(&task->mutex);
    }
    return NULL;
}

int main() {
    Task189 task;
    task.n = 5;
    task.current = 1;
    pthread_mutex_init(&task.mutex, NULL);
    pthread_cond_init(&task.cond, NULL);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero, &task);
    pthread_create(&t2, NULL, even, &task);
    pthread_create(&t3, NULL, odd, &task);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&task.mutex);
    pthread_cond_destroy(&task.cond);

    return 0;
}