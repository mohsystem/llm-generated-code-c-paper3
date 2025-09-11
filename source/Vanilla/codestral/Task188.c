#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    int n;
    sem_t fooSemaphore;
    sem_t barSemaphore;
} FooBar;

void *foo(void *arg) {
    FooBar *fooBar = (FooBar *)arg;
    for (int i = 0; i < fooBar->n; i++) {
        sem_wait(&fooBar->fooSemaphore);
        printf("foo");
        sem_post(&fooBar->barSemaphore);
    }
    return NULL;
}

void *bar(void *arg) {
    FooBar *fooBar = (FooBar *)arg;
    for (int i = 0; i < fooBar->n; i++) {
        sem_wait(&fooBar->barSemaphore);
        printf("bar\n");
        sem_post(&fooBar->fooSemaphore);
    }
    return NULL;
}

int main() {
    FooBar fooBar;
    fooBar.n = 2;
    sem_init(&fooBar.fooSemaphore, 0, 1);
    sem_init(&fooBar.barSemaphore, 0, 0);

    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, foo, &fooBar);
    pthread_create(&threadB, NULL, bar, &fooBar);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}