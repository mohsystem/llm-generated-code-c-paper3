#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t fooMutex;
    pthread_mutex_t barMutex;
} Task188;

void* foo(void* arg) {
    Task188* fb = (Task188*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->fooMutex);
        printf("foo");
        pthread_mutex_unlock(&fb->barMutex);
    }
    return NULL;
}

void* bar(void* arg) {
    Task188* fb = (Task188*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->barMutex);
        printf("bar");
        pthread_mutex_unlock(&fb->fooMutex);
    }
    return NULL;
}

int main() {
    int testCases[] = {1, 2, 3, 4, 5};
    for (int n : testCases) {
        Task188 fb;
        fb.n = n;
        pthread_mutex_init(&fb.fooMutex, NULL);
        pthread_mutex_init(&fb.barMutex, NULL);
        pthread_mutex_lock(&fb.barMutex); // Initially lock barMutex

        pthread_t fooThread, barThread;
        pthread_create(&fooThread, NULL, foo, &fb);
        pthread_create(&barThread, NULL, bar, &fb);

        pthread_join(fooThread, NULL);
        pthread_join(barThread, NULL);
        printf("\n");

        pthread_mutex_destroy(&fb.fooMutex);
        pthread_mutex_destroy(&fb.barMutex);
    }
    return 0;
}