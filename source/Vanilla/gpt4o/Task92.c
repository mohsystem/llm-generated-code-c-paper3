#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
const int maxCounter = 10;
pthread_mutex_t lock;

void* counterThread(void* arg) {
    int threadId = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&lock);
        if (currentCounter <= maxCounter) {
            printf("Thread %d is accessing currentCounter: %d\n", threadId, currentCounter);
            currentCounter++;
        } else {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    pthread_mutex_init(&lock, NULL);
    int threadIds[5];
    for (int i = 0; i < 5; i++) {
        threadIds[i] = i + 1;
        pthread_create(&threads[i], NULL, counterThread, &threadIds[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&lock);
    return 0;
}