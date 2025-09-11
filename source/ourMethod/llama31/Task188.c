#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t fooSemaphore;
sem_t barSemaphore;

void* foo(void* arg) {
    int n = *(int*)arg;
    for (int i = 0; i < n; i++) {
        sem_wait(&fooSemaphore);
        printf("foo");
        sem_post(&barSemaphore);
    }
    return NULL;
}

void* bar(void* arg) {
    int n = *(int*)arg;
    for (int i = 0; i < n; i++) {
        sem_wait(&barSemaphore);
        printf("bar");
        sem_post(&fooSemaphore);
    }
    return NULL;
}

int main() {
    int n = 5;
    sem_init(&fooSemaphore, 0, 1);
    sem_init(&barSemaphore, 0, 0);

    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, foo, &n);
    pthread_create(&threadB, NULL, bar, &n);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    sem_destroy(&fooSemaphore);
    sem_destroy(&barSemaphore);

    return 0;
}