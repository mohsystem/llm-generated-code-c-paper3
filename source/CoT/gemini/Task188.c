#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int turn;
} FooBar;

void *foo(void *arg) {
    FooBar *foobar = (FooBar *)arg;
    for (int i = 0; i < foobar->n; i++) {
        pthread_mutex_lock(&foobar->mutex);
        while (foobar->turn != 0) {
            pthread_cond_wait(&foobar->cond, &foobar->mutex);
        }
        printf("foo");
        foobar->turn = 1;
        pthread_cond_signal(&foobar->cond);
        pthread_mutex_unlock(&foobar->mutex);
    }
    return NULL;
}

void *bar(void *arg) {
    FooBar *foobar = (FooBar *)arg;
    for (int i = 0; i < foobar->n; i++) {
        pthread_mutex_lock(&foobar->mutex);
        while (foobar->turn != 1) {
            pthread_cond_wait(&foobar->cond, &foobar->mutex);
        }
        printf("bar");
        foobar->turn = 0;
        pthread_cond_signal(&foobar->cond);
        pthread_mutex_unlock(&foobar->mutex);
    }
    return NULL;
}

int main() {
    int test_cases[] = {1, 2, 3, 4, 5};
    for (int n_case = 0; n_case < 5; n_case++) {
        int n = test_cases[n_case];
        FooBar foobar;
        foobar.n = n;
        foobar.turn = 0;
        pthread_mutex_init(&foobar.mutex, NULL);
        pthread_cond_init(&foobar.cond, NULL);

        pthread_t foo_thread, bar_thread;
        pthread_create(&foo_thread, NULL, foo, &foobar);
        pthread_create(&bar_thread, NULL, bar, &foobar);

        pthread_join(foo_thread, NULL);
        pthread_join(bar_thread, NULL);
        printf("\n");

        pthread_mutex_destroy(&foobar.mutex);
        pthread_cond_destroy(&foobar.cond);
    }
    return 0;
}