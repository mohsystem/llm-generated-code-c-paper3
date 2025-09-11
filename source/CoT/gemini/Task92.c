#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
int maxCounter;
pthread_mutex_t lock;

void* incrementCounter(void* arg) {
    int threadId = *(int*)arg;

    if (currentCounter <= maxCounter) {
        pthread_mutex_lock(&lock);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            printf("Thread %d accessed counter: %d\n", threadId, currentCounter);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main() {
    maxCounter = 5;
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[5];
    int threadIds[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        for (int j=0; j< 10; ++j){
            pthread_create(&threads[i], NULL, incrementCounter, &threadIds[i]);
        }
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}