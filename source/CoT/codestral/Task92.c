#include <stdio.h>
#include <pthread.h>

int currentCounter = 0;
const int maxCounter = 5;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* updateCounter(void* threadid) {
    long tid;
    tid = (long)threadid;
    if (currentCounter <= maxCounter) {
        pthread_mutex_lock(&lock);
        currentCounter++;
        printf("Thread %ld is accessing currentCounter: %d\n", tid, currentCounter);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[10];
    int rc;
    long t;
    for(t=0; t<10; t++) {
        rc = pthread_create(&threads[t], NULL, updateCounter, (void *)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            return -1;
        }
    }
    for(t=0; t<10; t++) {
        pthread_join(threads[t], NULL);
    }
    pthread_exit(NULL);
    return 0;
}