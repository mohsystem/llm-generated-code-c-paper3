#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t foo_mutex;
    pthread_mutex_t bar_mutex;
    pthread_cond_t cond;
    int turn;
} FooBar;

void* foo(void* arg) {
    FooBar* fb = (FooBar*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->foo_mutex);
        while (fb->turn != 0) {
            pthread_cond_wait(&fb->cond, &fb->foo_mutex);
        }
        printf("foo");
        fb->turn = 1;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->foo_mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    FooBar* fb = (FooBar*) arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->bar_mutex);
        while (fb->turn != 1) {
            pthread_cond_wait(&fb->cond, &fb->bar_mutex);
        }
        printf("bar");
        fb->turn = 0;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->bar_mutex);

    }
    return NULL;
}

int main() {
    int test_cases[] = {1, 2, 3, 4, 5};
    for (int n_val : test_cases) {
        FooBar fb;
        fb.n = n_val;
        fb.turn = 0;
        pthread_mutex_init(&fb.foo_mutex, NULL);
        pthread_mutex_init(&fb.bar_mutex, NULL);
        pthread_cond_init(&fb.cond, NULL);


        pthread_t t1, t2;
        pthread_create(&t1, NULL, foo, &fb);
        pthread_create(&t2, NULL, bar, &fb);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("\n");

        pthread_mutex_destroy(&fb.foo_mutex);
        pthread_mutex_destroy(&fb.bar_mutex);
        pthread_cond_destroy(&fb.cond);
    }
    return 0;
}