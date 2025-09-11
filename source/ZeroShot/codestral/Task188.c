// C does not have built-in threading support, so it's not possible to provide a complete solution in C.
// However, here's a sketch of how you might approach the problem using pthreads.

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int n;
    bool fooTurn;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
} FooBar;

void* foo(void* arg) {
    FooBar* fb = (FooBar*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mtx);
        while (!fb->fooTurn) {
            pthread_cond_wait(&fb->cv, &fb->mtx);
        }
        printf("foo");
        fb->fooTurn = false;
        pthread_mutex_unlock(&fb->mtx);
        pthread_cond_signal(&fb->cv);
    }
    return NULL;
}

void* bar(void* arg) {
    FooBar* fb = (FooBar*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mtx);
        while (fb->fooTurn) {
            pthread_cond_wait(&fb->cv, &fb->mtx);
        }
        printf("bar");
        fb->fooTurn = true;
        pthread_mutex_unlock(&fb->mtx);
        pthread_cond_signal(&fb->cv);
    }
    return NULL;
}

int main() {
    FooBar fb = {5, true, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
    pthread_t t1, t2;
    pthread_create(&t1, NULL, foo, &fb);
    pthread_create(&t2, NULL, bar, &fb);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}