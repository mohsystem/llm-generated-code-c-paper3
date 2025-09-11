#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int currentCounter = 0;
int maxCounter = 10;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* accessCounter(void* arg) {
    while (true) {
        pthread_mutex_lock(&lock);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            printf("Thread %ld is accessing currentCounter: %d\n", (long)pthread_self(), currentCounter);
        } else {
            break;
        }
        pthread_mutex_unlock(&lock);
        usleep(100000); // Add a small delay to avoid rapid execution
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, accessCounter, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}