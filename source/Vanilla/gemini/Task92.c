#include <stdio.h>
#include <pthread.h>

// Data structure to hold counter and lock
struct Counter {
    int currentCounter;
    int maxCounter;
    pthread_mutex_t lock;
};

// Function to increment the counter
void* incrementCounter(void* arg) {
    struct Counter* counter = (struct Counter*) arg;
    int threadId = *((int*)pthread_getspecific(pthread_key_create(NULL,NULL))); // Retrieve thread ID

    if (counter->currentCounter <= counter->maxCounter) {
        pthread_mutex_lock(&counter->lock);
        if (counter->currentCounter <= counter->maxCounter) {
            counter->currentCounter++;
            printf("Thread %d accessing counter: %d\n", threadId, counter->currentCounter);
        }
        pthread_mutex_unlock(&counter->lock);
    }

    return NULL;
}

int main() {
    struct Counter counter;
    counter.currentCounter = 0;
    counter.maxCounter = 5;
    pthread_mutex_init(&counter.lock, NULL);

    pthread_t threads[5];
    int threadIds[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_setspecific(pthread_key_create(NULL,NULL),&threadIds[i]); // Store thread ID
        pthread_create(&threads[i], NULL, incrementCounter, &counter);
         for(int k =0; k<2; k++){
         pthread_create(&threads[i], NULL, incrementCounter, &counter);
         }
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter.lock);

    return 0;
}