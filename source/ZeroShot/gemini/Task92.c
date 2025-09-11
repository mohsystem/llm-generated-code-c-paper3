#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

typedef struct {
    atomic_int currentCounter;
    int maxCounter;
    pthread_mutex_t lock;
} Counter;

void *increment_and_print(void *arg) {
    Counter *counter = (Counter *)arg;
    int threadId = *(int *)((char *)arg + sizeof(Counter)); 

    while (atomic_load(&counter->currentCounter) <= counter->maxCounter) {
        pthread_mutex_lock(&counter->lock);
        if (atomic_load(&counter->currentCounter) <= counter->maxCounter) {
            atomic_fetch_add(&counter->currentCounter, 1);
            printf("Thread %d accessing currentCounter: %d\n", threadId, atomic_load(&counter->currentCounter));
        }
        pthread_mutex_unlock(&counter->lock);
    }

    return NULL;
}

int main() {
    Counter counter;
    counter.currentCounter = 0;
    counter.maxCounter = 5;
    pthread_mutex_init(&counter.lock, NULL);

    pthread_t threads[5];
    int threadIds[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
         char *arg = malloc(sizeof(Counter) + sizeof(int));
        *(Counter*)arg = counter;
        *(int*)((char*)arg + sizeof(Counter)) = threadIds[i];

        pthread_create(&threads[i], NULL, increment_and_print, arg);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counter.lock);
    return 0;
}