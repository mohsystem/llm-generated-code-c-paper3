
// C does not have built-in thread support.
// For thread programming in C, you would need to use platform-specific libraries like pthreads on Unix/Linux
// or Windows threads on Windows. Here's a simplified version using pthreads:

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNTER 10

static int currentCounter = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadArgs {
    char name[20];
};

void* worker(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    
    while(1) {
        if(currentCounter <= MAX_COUNTER) {
            pthread_mutex_lock(&mutex);
            if(currentCounter <= MAX_COUNTER) {
                printf("%s accessing counter: %d\\n", args->name, currentCounter);
                currentCounter++;
            }
            pthread_mutex_unlock(&mutex);
        } else {
            break;
        }
    }
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[5];
    
    // Test case 1: Create 3 threads
    currentCounter = 0;
    for(int i = 0; i < 3; i++) {
        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        sprintf(args->name, "Thread-%d", i+1);
        pthread_create(&threads[i], NULL, worker, args);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Test case 2: Create 2 threads
    currentCounter = 0;
    for(int i = 0; i < 2; i++) {
        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        sprintf(args->name, "Thread-%d", i+4);
        pthread_create(&threads[i], NULL, worker, args);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Test case 3: Single thread
    currentCounter = 0;
    struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
    sprintf(args->name, "Thread-6");
    pthread_create(&threads[0], NULL, worker, args);
    pthread_join(threads[0], NULL);
    
    // Test case 4: 4 threads
    currentCounter = 0;
    for(int i = 0; i < 4; i++) {
        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        sprintf(args->name, "Thread-%d", i+7);
        pthread_create(&threads[i], NULL, worker, args);
    }
    for(int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Test case 5: 5 threads
    currentCounter = 0;
    for(int i = 0; i < 5; i++) {
        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        sprintf(args->name, "Thread-%d", i+11);
        pthread_create(&threads[i], NULL, worker, args);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
