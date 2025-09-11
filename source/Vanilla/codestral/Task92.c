// C language does not have built-in thread support, so it's not possible to provide a thread-safe solution.
// The code below is not thread-safe and may produce incorrect results when run in a multi-threaded environment.

#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
int maxCounter = 5;
pthread_mutex_t lock;

void* accessResource(void* threadNumber) {
    pthread_mutex_lock(&lock);
    if (currentCounter <= maxCounter) {
        currentCounter++;
        printf("Thread %d is accessing the currentCounter: %d\n", *((int*)threadNumber), currentCounter);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[10];
    int threadNumbers[10];
    pthread_mutex_init(&lock, NULL);
    for (int i = 1; i <= 10; i++) {
        threadNumbers[i - 1] = i;
        pthread_create(&threads[i - 1], NULL, accessResource, &threadNumbers[i - 1]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}