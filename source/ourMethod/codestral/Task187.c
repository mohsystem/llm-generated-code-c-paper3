/* C does not support threads natively, so this solution uses POSIX threads (pthreads) */
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t hydrogen;
sem_t oxygen;

void releaseHydrogen() {
    sem_wait(&hydrogen);
    printf("H");
    int value;
    sem_getvalue(&hydrogen, &value);
    if (value == 0 && sem_getvalue(&oxygen, &value) < 0) {
        sem_post(&oxygen);
        sem_post(&oxygen);
    }
}

void releaseOxygen() {
    sem_wait(&oxygen);
    sem_wait(&oxygen);
    printf("O");
    sem_post(&hydrogen);
    sem_post(&hydrogen);
}

int main() {
    sem_init(&hydrogen, 0, 2);
    sem_init(&oxygen, 0, 0);

    for (int i = 0; i < 10; i++) {
        pthread_t t1, t2;
        pthread_create(&t1, NULL, (void *)releaseHydrogen, NULL);
        pthread_create(&t2, NULL, (void *)releaseOxygen, NULL);
        pthread_detach(t1);
        pthread_detach(t2);
    }

    /* The main thread should wait for the other threads to finish */
    pthread_exit(NULL);
}