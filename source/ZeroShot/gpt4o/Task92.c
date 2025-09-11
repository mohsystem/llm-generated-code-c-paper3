#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

pthread_mutex_t lock;
int currentCounter = 0;
const int maxCounter = 5;

void* accessCounter(void* arg) {
    int threadId = *(int*)arg;
    pthread_mutex_lock(&lock);
    if (currentCounter <= maxCounter) {
        printf("Thread %d accessing counter: %d\n", threadId, currentCounter);
        currentCounter++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[MAX_THREADS];
    int threadIds[MAX_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < MAX_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, accessCounter, &threadIds[i]);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}