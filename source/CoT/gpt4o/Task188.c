#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t fooSemaphore;
    sem_t barSemaphore;
} FooBar;

void init(FooBar *obj, int n) {
    obj->n = n;
    sem_init(&obj->fooSemaphore, 0, 1);
    sem_init(&obj->barSemaphore, 0, 0);
}

void* foo(void* arg) {
    FooBar* obj = (FooBar*)arg;
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->fooSemaphore);
        printf("foo");
        sem_post(&obj->barSemaphore);
    }
    return NULL;
}

void* bar(void* arg) {
    FooBar* obj = (FooBar*)arg;
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->barSemaphore);
        printf("bar");
        sem_post(&obj->fooSemaphore);
    }
    return NULL;
}

void run_test(int n) {
    FooBar obj;
    init(&obj, n);

    pthread_t threadFoo, threadBar;

    pthread_create(&threadFoo, NULL, foo, &obj);
    pthread_create(&threadBar, NULL, bar, &obj);

    pthread_join(threadFoo, NULL);
    pthread_join(threadBar, NULL);
}

int main() {
    run_test(1);
    printf("\n");
    run_test(2);
    printf("\n");
    run_test(3);
    printf("\n");
    run_test(4);
    printf("\n");
    run_test(5);
    printf("\n");
    return 0;
}