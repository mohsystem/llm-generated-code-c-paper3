
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNTER 5
#define NUM_THREADS 3

typedef struct {
    int currentCounter;
    pthread_mutex_t mutex;
    char threadName[20];
} ThreadData;

void* worker(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    while (1) {
        pthread_mutex_lock(&data->mutex);
        if (data->currentCounter >= MAX_COUNTER) {
            pthread_mutex_unlock(&data->mutex);
            break;
        }
        data->currentCounter++;
        printf("%s accessing counter. Current value: %d\\n", 
               data->threadName, data->currentCounter);
        pthread_mutex_unlock(&data->mutex);
        usleep(100000);  // 100ms sleep
    }
    
    return NULL;
}

int main() {
    ThreadData data;
    pthread_t threads[NUM_THREADS];
    data.currentCounter = 0;
    pthread_mutex_init(&data.mutex, NULL);

    // Test case 1: Create and start 3 threads
    for (int i = 0; i < NUM_THREADS; i++) {
        snprintf(data.threadName, sizeof(data.threadName), "Thread-%d", i+1);
        if (pthread_create(&threads[i], NULL, worker, &data) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }

    // Test case 2: Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Test case 3: Reset counter and create 2 more threads
    pthread_mutex_lock(&data.mutex);
    data.currentCounter = 0;
    pthread_mutex_unlock(&data.mutex);
    
    pthread_t threads2[2];
    for (int i = 0; i < 2; i++) {
        snprintf(data.threadName, sizeof(data.threadName), "Thread-%d", i+4);
        if (pthread_create(&threads2[i], NULL, worker, &data) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }

    // Test case 4: Wait for second batch to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(threads2[i], NULL);
    }

    // Test case 5: Verify final counter value
    pthread_mutex_lock(&data.mutex);
    printf("Final counter value: %d\\n", data.currentCounter);
    pthread_mutex_unlock(&data.mutex);

    pthread_mutex_destroy(&data.mutex);
    return 0;
}
