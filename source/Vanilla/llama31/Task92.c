#include <stdio.h>
#include <pthread.h>

typedef struct {
    int maxCounter;
    int currentCounter;
    pthread_mutex_t mutex;
} Counter;

void* incrementAndPrint(void* arg) {
    Counter* counter = (Counter*)arg;
    int threadId = *(int*)arg + 1; // Assuming arg is a pointer to an int

    pthread_mutex_lock(&counter->mutex);
    if (counter->currentCounter <= counter->maxCounter) {
        counter->currentCounter++;
        printf("Thread %d is accessing currentCounter: %d\n", threadId, counter->currentCounter);
    }
    pthread_mutex_unlock(&counter->mutex);

    return NULL;
}

int main() {
    Counter counter;
    counter.maxCounter = 5;
    counter.currentCounter = 0;
    pthread_mutex_init(&counter.mutex, NULL);

    pthread_t threads[10];
    int threadIds[10];

    for (int i = 0; i < 10; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, incrementAndPrint, &threadIds[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter.mutex);

    return 0;
}