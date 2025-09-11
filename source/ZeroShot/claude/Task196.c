
// Note: C doesn't have built-in support for threading and object-oriented programming.\n// Here's a simplified version using pthreads, but it's not recommended for production use.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int n;
    int state;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ZeroEvenOdd;

void printNumber(int x) {
    printf("%d", x);
}

void* zero_func(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 0; i < zeo->n; i++) {
        pthread_mutex_lock(&zeo->mutex);
        while (zeo->state != 0) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(0);
        zeo->state = (i % 2 == 0) ? 1 : 2;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void* even_func(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 2; i <= zeo->n; i += 2) {
        pthread_mutex_lock(&zeo->mutex);
        while (zeo->state != 2) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(i);
        zeo->state = 0;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void* odd_func(void* arg) {
    ZeroEvenOdd* zeo = (ZeroEvenOdd*)arg;
    for (int i = 1; i <= zeo->n; i += 2) {
        pthread_mutex_lock(&zeo->mutex);
        while (zeo->state != 1) {
            pthread_cond_wait(&zeo->cond, &zeo->mutex);
        }
        printNumber(i);
        zeo->state = 0;
        pthread_cond_broadcast(&zeo->cond);
        pthread_mutex_unlock(&zeo->mutex);
    }
    return NULL;
}

void test_case(int n) {
    printf("Test case n = %d\\n", n);
    
    ZeroEvenOdd zeo;
    zeo.n = n;
    zeo.state = 0;
    pthread_mutex_init(&zeo.mutex, NULL);
    pthread_cond_init(&zeo.cond, NULL);
    
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, zero_func, &zeo);
    pthread_create(&t2, NULL, even_func, &zeo);
    pthread_create(&t3, NULL, odd_func, &zeo);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    pthread_mutex_destroy(&zeo.mutex);
    pthread_cond_destroy(&zeo.cond);
    
    printf("\\n\\n");
}

int main() {
    int test_cases[] = {2, 5, 1, 3, 4};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        test_case(test_cases[i]);
    }
    
    return 0;
}
