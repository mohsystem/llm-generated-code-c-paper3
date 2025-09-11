#include <stdio.h>
#include <pthread.h>

typedef struct {
    int n;
    int current;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} FooBar;

void *foo(void *arg) {
    FooBar *fb = (FooBar *)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->current % 2 != 0) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("foo");
        fb->current++;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

void *bar(void *arg) {
    FooBar *fb = (FooBar *)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->current % 2 != 1) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("bar");
        fb->current++;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

int main() {
    void test(int n) {
        FooBar fb;
        fb.n = n;
        fb.current = 0;
        pthread_mutex_init(&fb.mutex, NULL);
        pthread_cond_init(&fb.cond, NULL);

        pthread_t t1, t2;
        pthread_create(&t1, NULL, foo, &fb);
        pthread_create(&t2, NULL, bar, &fb);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("\n");

        pthread_mutex_destroy(&fb.mutex);
        pthread_cond_destroy(&fb.cond);
    }
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    return 0;
}