#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
    int n;
    sem_t fooSemaphore;
    sem_t barSemaphore;
    int counter;
} FooBar;

void foo(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->fooSemaphore);
        printf("foo");
        sem_post(&obj->barSemaphore);
    }
}

void bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->barSemaphore);
        printf("bar");
        sem_post(&obj->fooSemaphore);
    }
}

int main() {
    FooBar fooBar;
    fooBar.n = 3;
    fooBar.counter = 0;
    sem_init(&fooBar.fooSemaphore, 0, 1);
    sem_init(&fooBar.barSemaphore, 0, 0);

    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, (void*)foo, &fooBar);
    pthread_create(&threadB, NULL, (void*)bar, &fooBar);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}