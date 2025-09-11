#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int foo_turn = 1;
int n;

void* foo(void* arg) {
    for (int i = 0; i < n; ++i) {
        pthread_mutex_lock(&mutex);
        while (!foo_turn) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("foo");
        foo_turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    for (int i = 0; i < n; ++i) {
        pthread_mutex_lock(&mutex);
        while (foo_turn) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("bar");
        foo_turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    n = 5;
    pthread_t thread_a, thread_b;

    pthread_create(&thread_a, NULL, foo, NULL);
    pthread_create(&thread_b, NULL, bar, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    return 0;
}