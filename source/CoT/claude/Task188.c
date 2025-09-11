
// C doesn't have built-in thread support and object-oriented features\n// For a C implementation, you would need to use platform-specific threading libraries\n// like pthread or Windows threads. Here's a basic example using pthread:

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int n;
    int fooTurn;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Task188;

void* foo(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (!fb->fooTurn) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("foo");
        fb->fooTurn = 0;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    Task188* fb = (Task188*)arg;
    for (int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while (fb->fooTurn) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("bar");
        fb->fooTurn = 1;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

int main() {
    int testCases[] = {1, 2, 3, 5, 10};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int t = 0; t < numTests; t++) {
        printf("\\nTest case n = %d\\n", testCases[t]);
        
        Task188* fb = malloc(sizeof(Task188));
        if (!fb) {
            fprintf(stderr, "Memory allocation failed\\n");
            return 1;
        }
        
        fb->n = testCases[t];
        fb->fooTurn = 1;
        pthread_mutex_init(&fb->mutex, NULL);
        pthread_cond_init(&fb->cond, NULL);
        
        pthread_t threadA, threadB;
        pthread_create(&threadA, NULL, foo, fb);
        pthread_create(&threadB, NULL, bar, fb);
        
        pthread_join(threadA, NULL);
        pthread_join(threadB, NULL);
        
        pthread_mutex_destroy(&fb->mutex);
        pthread_cond_destroy(&fb->cond);
        free(fb);
    }
    
    return 0;
}
