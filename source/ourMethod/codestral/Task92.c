#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
const int maxCounter = 10;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *incrementCounter(void *arg) {
    if (currentCounter <= maxCounter) {
        pthread_mutex_lock(&mtx);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            printf("Thread %ld is accessing the currentCounter at this moment. Current counter value: %d\n", pthread_self(), currentCounter);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    pthread_t threads[20];
    for (int i = 0; i < 20; i++) {
        pthread_create(&threads[i], NULL, incrementCounter, NULL);
    }
    for (int i = 0; i < 20; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}