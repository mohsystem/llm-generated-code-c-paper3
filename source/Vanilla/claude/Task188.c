
// C does not have built-in threading support.
// Need to use platform specific threading libraries like pthread
// Here's a basic implementation using pthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct Task188 {
    int n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int isFoo;
};

void* foo(void* arg) {
    struct Task188* fb = (struct Task188*)arg;
    for(int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while(!fb->isFoo) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("foo");
        fb->isFoo = 0;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

void* bar(void* arg) {
    struct Task188* fb = (struct Task188*)arg;
    for(int i = 0; i < fb->n; i++) {
        pthread_mutex_lock(&fb->mutex);
        while(fb->isFoo) {
            pthread_cond_wait(&fb->cond, &fb->mutex);
        }
        printf("bar");
        fb->isFoo = 1;
        pthread_cond_signal(&fb->cond);
        pthread_mutex_unlock(&fb->mutex);
    }
    return NULL;
}

int main() {
    int test_cases[] = {1, 2, 3, 4, 5};
    
    for(int t = 0; t < 5; t++) {
        printf("\\nTest case n = %d\\n", test_cases[t]);
        
        struct Task188 fb;
        fb.n = test_cases[t];
        fb.isFoo = 1;
        pthread_mutex_init(&fb.mutex, NULL);
        pthread_cond_init(&fb.cond, NULL);
        
        pthread_t t1, t2;
        pthread_create(&t1, NULL, foo, &fb);
        pthread_create(&t2, NULL, bar, &fb);
        
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        
        pthread_mutex_destroy(&fb.mutex);
        pthread_cond_destroy(&fb.cond);
    }
    
    return 0;
}
