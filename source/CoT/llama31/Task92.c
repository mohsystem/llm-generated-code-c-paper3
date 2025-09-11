#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int currentCounter = 0;
int maxCounter = 10;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* threadMethod(void* arg) {
    char* threadName = (char*)arg;
    while (true) {
        pthread_mutex_lock(&lock);
        if (currentCounter <= maxCounter) {
            currentCounter++;
            printf("%s is accessing currentCounter: %d\n", threadName, currentCounter);
        } else {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
        usleep(100000); // Add a small delay to avoid busy-waiting
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    char threadNames[5][10];
    for (int i = 0; i < 5; i++) {
        sprintf(threadNames[i], "Thread-%d", i);
        pthread_create(&threads[i], NULL, threadMethod, threadNames[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}