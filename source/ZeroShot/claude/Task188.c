
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int state;
} Task188;

void* foo(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->state != 0) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("foo");
        fb->state = 1;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->state != 1) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("bar");
        fb->state = 0;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

int main() {
    int test_cases[] = {1, 2, 3, 4, 5};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int t = 0; t < num_tests; t++) {
        printf("\\nTest case n = %d:\\n", test_cases[t]);
        
        Task188* fb = malloc(sizeof(Task188));
        fb->n = test_cases[t];
        fb->state = 0;
        pthread_mutex_init(&fb->mutex, NULL);
        pthread_cond_init(&fb->cond, NULL);
        
        pthread_t thread1, thread2;
        pthread_create(&thread1, NULL, foo, fb);
        pthread_create(&thread2, NULL, bar, fb);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        
        pthread_mutex_destroy(&fb->mutex);
        pthread_cond_destroy(&fb->cond);
        free(fb);
    }
    
    return 0;
}
