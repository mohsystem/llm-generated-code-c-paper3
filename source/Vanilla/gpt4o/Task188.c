#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int foo_turn;
} FooBar;

void FooBar_init(FooBar* fooBar, int n) {
    fooBar->n = n;
    pthread_mutex_init(&fooBar->mutex, NULL);
    pthread_cond_init(&fooBar->cond, NULL);
    fooBar->foo_turn = 1;
}

void* foo(void* arg) {
    FooBar* fooBar = (FooBar*)arg;
    for (int i = 0; i < fooBar->n; i++) {
        pthread_mutex_lock(&fooBar->mutex);
        while (!fooBar->foo_turn) {
            pthread_cond_wait(&fooBar->cond, &fooBar->mutex);
        }
        printf("foo");
        fooBar->foo_turn = 0;
        pthread_cond_signal(&fooBar->cond);
        pthread_mutex_unlock(&fooBar->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    FooBar* fooBar = (FooBar*)arg;
    for (int i = 0; i < fooBar->n; i++) {
        pthread_mutex_lock(&fooBar->mutex);
        while (fooBar->foo_turn) {
            pthread_cond_wait(&fooBar->cond, &fooBar->mutex);
        }
        printf("bar");
        fooBar->foo_turn = 1;
        pthread_cond_signal(&fooBar->cond);
        pthread_mutex_unlock(&fooBar->mutex);
    }
    return NULL;
}

void test_foobar(int n) {
    FooBar fooBar;
    FooBar_init(&fooBar, n);

    pthread_t thread_foo, thread_bar;
    pthread_create(&thread_foo, NULL, foo, &fooBar);
    pthread_create(&thread_bar, NULL, bar, &fooBar);

    pthread_join(thread_foo, NULL);
    pthread_join(thread_bar, NULL);

    pthread_mutex_destroy(&fooBar.mutex);
    pthread_cond_destroy(&fooBar.cond);
}

int main() {
    test_foobar(1);
    test_foobar(2);
    test_foobar(3);
    test_foobar(4);
    test_foobar(5);
    return 0;
}