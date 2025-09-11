#include <stdio.h>
#include <pthread.h>

int current_counter = 0;
int max_counter = 5;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* id) {
    int thread_id = *((int*)id);
    while (1) {
        pthread_mutex_lock(&mtx);
        if (current_counter < max_counter) {
            current_counter++;
            printf("Thread %d is accessing the currentCounter at this moment.\n", thread_id);
        } else {
            pthread_mutex_unlock(&mtx);
            break;
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}