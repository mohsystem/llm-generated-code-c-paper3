
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNTER 10

typedef struct {
    int* current_counter;
    pthread_mutex_t* mutex;
    char thread_name[20];
} ThreadArgs;

void* increment_counter(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    while (1) {
        pthread_mutex_lock(args->mutex);
        if (*(args->current_counter) >= MAX_COUNTER) {
            pthread_mutex_unlock(args->mutex);
            break;
        }
        (*(args->current_counter))++;
        printf("Thread %s accessing counter: %d\\n", args->thread_name, *(args->current_counter));
        pthread_mutex_unlock(args->mutex);
        usleep(100000); // 100ms sleep
    }
    return NULL;
}

int main() {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int current_counter = 0;
    
    // Test case 1: Create 3 threads
    pthread_t threads[5];
    ThreadArgs args[5];
    
    for (int i = 0; i < 3; i++) {
        args[i].current_counter = &current_counter;
        args[i].mutex = &mutex;
        sprintf(args[i].thread_name, "T%d", i+1);
        pthread_create(&threads[i], NULL, increment_counter, &args[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Test case 2: Reset counter
    current_counter = 0;
    
    // Test case 3: Create 5 threads
    for (int i = 0; i < 5; i++) {
        args[i].current_counter = &current_counter;
        args[i].mutex = &mutex;
        sprintf(args[i].thread_name, "Thread-%d", i);
        pthread_create(&threads[i], NULL, increment_counter, &args[i]);
    }
    
    // Test case 4: Wait for all threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Test case 5: Final counter check
    printf("Final counter value: %d\\n", current_counter);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
