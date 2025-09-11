#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
const int maxCounter = 10;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* incrementCounter(void* arg) {
    int threadId = *(int*)arg;
    for (int j = 0; j < 5; j++) {
        pthread_mutex_lock(&lock);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            printf("Thread %d is accessing the currentCounter: %d\n", threadId, currentCounter);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    int threadIds[5];
    for (int i = 0; i < 5; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, incrementCounter, &threadIds[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}