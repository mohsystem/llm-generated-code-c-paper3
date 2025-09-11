#include <stdio.h>
#include <pthread.h>

#define N 5

int current = 1;
pthread_mutex_t zero_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t even_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t odd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void* zero(void* arg) {
    for (int i = 1; i <= N; ++i) {
        pthread_mutex_lock(&zero_mutex);
        while (current > N) {
            pthread_cond_wait(&cv, &zero_mutex);
        }
        printf("0");
        if (current % 2 == 0) {
            pthread_mutex_unlock(&even_mutex);
        } else {
            pthread_mutex_unlock(&odd_mutex);
        }
        ++current;
    }
    return NULL;
}

void* even(void* arg) {
    for (int i = 2; i <= N; i += 2) {
        pthread_mutex_lock(&even_mutex);
        while (current != i) {
            pthread_cond_wait(&cv, &even_mutex);
        }
        printf("%d", i);
        pthread_mutex_unlock(&zero_mutex);
    }
    return NULL;
}

void* odd(void* arg) {
    for (int i = 1; i <= N; i += 2) {
        pthread_mutex_lock(&odd_mutex);
        while (current != i) {
            pthread_cond_wait(&cv, &odd_mutex);
        }
        printf("%d", i);
        pthread_mutex_unlock(&zero_mutex);
    }
    return NULL;
}

int main() {
    pthread_mutex_lock(&even_mutex);
    pthread_mutex_lock(&odd_mutex);

    pthread_t threadA, threadB, threadC;
    pthread_create(&threadA, NULL, zero, NULL);
    pthread_create(&threadB, NULL, even, NULL);
    pthread_create(&threadC, NULL, odd, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}