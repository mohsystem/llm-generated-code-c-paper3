
// C does not have built-in thread support
// This would require platform specific threading libraries like pthreads
// Here's a pseudo-code structure of how it would work

/*
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t zero_sem;
    sem_t even_sem;
    sem_t odd_sem;
    int current;
} Task189;

void init(Task189* obj, int n) {
    obj->n = n;
    obj->current = 1;
    sem_init(&obj->zero_sem, 0, 1);
    sem_init(&obj->even_sem, 0, 0);
    sem_init(&obj->odd_sem, 0, 0);
}

void zero(Task189* obj) {
    for(int i = 1; i <= obj->n; i++) {
        sem_wait(&obj->zero_sem);
        printf("0");
        if(i % 2 == 0)
            sem_post(&obj->even_sem);
        else
            sem_post(&obj->odd_sem);
    }
}

void even(Task189* obj) {
    for(int i = 2; i <= obj->n; i+=2) {
        sem_wait(&obj->even_sem);
        printf("%d", i);
        sem_post(&obj->zero_sem);
    }
}

void odd(Task189* obj) {
    for(int i = 1; i <= obj->n; i+=2) {
        sem_wait(&obj->odd_sem);
        printf("%d", i);
        sem_post(&obj->zero_sem);
    }
}
*/
