#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int fooTurn;
} FooBar;

void* foo(void* arg) {
    FooBar* fooBar = (FooBar*)arg;
    for (int i = 0; i < fooBar->n; i++) {
        pthread_mutex_lock(&fooBar->mutex);
        while (!fooBar->fooTurn) {
            pthread_cond_wait(&fooBar->cond, &fooBar->mutex);
        }
        printf("foo");
        fooBar->fooTurn = 0;
        pthread_cond_signal(&fooBar->cond);
        pthread_mutex_unlock(&fooBar->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    FooBar* fooBar = (FooBar*)arg;
    for (int i = 0; i < fooBar->n; i++) {
        pthread_mutex_lock(&fooBar->mutex);
        while (fooBar->fooTurn) {
            pthread_cond_wait(&fooBar->cond, &fooBar->mutex);
        }
        printf("bar");
        fooBar->fooTurn = 1;
        pthread_cond_signal(&fooBar->cond);
        pthread_mutex_unlock(&fooBar->mutex);
    }
    return NULL;
}

void runTestCases(int n) {
    FooBar fooBar = {n, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 1};
    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, foo, &fooBar);
    pthread_create(&threadB, NULL, bar, &fooBar);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
}

int main() {
    runTestCases(1);
    return 0;
}