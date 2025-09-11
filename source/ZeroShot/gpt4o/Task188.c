#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t fooSemaphore;
    sem_t barSemaphore;
} Task188;

void* foo(void* arg) {
    Task188* task = (Task188*)arg;
    for (int i = 0; i < task->n; ++i) {
        sem_wait(&task->fooSemaphore);
        printf("foo");
        sem_post(&task->barSemaphore);
    }
    return NULL;
}

void* bar(void* arg) {
    Task188* task = (Task188*)arg;
    for (int i = 0; i < task->n; ++i) {
        sem_wait(&task->barSemaphore);
        printf("bar");
        sem_post(&task->fooSemaphore);
    }
    return NULL;
}

void runTask(int n) {
    Task188 task;
    task.n = n;
    sem_init(&task.fooSemaphore, 0, 1);
    sem_init(&task.barSemaphore, 0, 0);

    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, foo, &task);
    pthread_create(&threadB, NULL, bar, &task);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    sem_destroy(&task.fooSemaphore);
    sem_destroy(&task.barSemaphore);

    printf("\n");
}

int main() {
    int testCases[] = {1, 2, 3, 5, 10};
    for (int i = 0; i < 5; ++i) {
        runTask(testCases[i]);
    }
    return 0;
}