
// Note: C doesn't have built-in thread support.\n// You would need to use platform-specific threading libraries like pthreads.\n// Here's a version using pthreads:

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int foo_turn;
} Task188;

void* foo(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (!fb->foo_turn) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("foo");
        fb->foo_turn = 0;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->foo_turn) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("bar");
        fb->foo_turn = 1;
        pthread_cond_broadcast(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

int main() {
    int test_cases[] = {1, 2, 3, 5, 10};
    int num_tests = 5;
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_cases[i];
        printf("\\nTest case n = %d:\\n", n);
        
        Task188* fb = malloc(sizeof(Task188));
        if (!fb) {
            fprintf(stderr, "Memory allocation failed\\n");
            return 1;
        }
        
        fb->n = n;
        fb->foo_turn = 1;
        
        if (pthread_mutex_init(&fb->mutex, NULL) != 0 ||
            pthread_cond_init(&fb->cond, NULL) != 0) {
            fprintf(stderr, "Mutex/Condition initialization failed\\n");
            free(fb);
            return 1;
        }
        
        pthread_t thread_a, thread_b;
        pthread_create(&thread_a, NULL, foo, fb);
        pthread_create(&thread_b, NULL, bar, fb);
        
        pthread_join(thread_a, NULL);
        pthread_join(thread_b, NULL);
        
        pthread_mutex_destroy(&fb->mutex);
        pthread_cond_destroy(&fb->cond);
        free(fb);
    }
    
    return 0;
}
