#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t fooSem;
    sem_t barSem;
} FooBar;

FooBar* FooBar_create(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    sem_init(&obj->fooSem, 0, 1);
    sem_init(&obj->barSem, 0, 0);
    return obj;
}

void* foo(void* p) {
    FooBar* obj = (FooBar*) p;
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->fooSem);
        printf("foo");
        sem_post(&obj->barSem);
    }
    return NULL;
}

void* bar(void* p) {
    FooBar* obj = (FooBar*) p;
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->barSem);
        printf("bar");
        sem_post(&obj->fooSem);
    }
    return NULL;
}

int main() {
    FooBar* obj = FooBar_create(2);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, foo, obj);
    pthread_create(&t2, NULL, bar, obj);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}