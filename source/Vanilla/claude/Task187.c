
// Note: C doesn't have built-in thread support.\n// You would need to use platform-specific threading libraries like pthreads.\n// Here's a simplified version using pthreads:

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    sem_t hydrogen_sem;
    sem_t oxygen_sem;
    sem_t barrier;
    pthread_mutex_t mutex;
    int hydrogen_count;
    int oxygen_count;
} Task187;

void init_task(Task187* task) {
    sem_init(&task->hydrogen_sem, 0, 2);
    sem_init(&task->oxygen_sem, 0, 1);
    sem_init(&task->barrier, 0, 0);
    pthread_mutex_init(&task->mutex, NULL);
    task->hydrogen_count = 0;
    task->oxygen_count = 0;
}

void destroy_task(Task187* task) {
    sem_destroy(&task->hydrogen_sem);
    sem_destroy(&task->oxygen_sem);
    sem_destroy(&task->barrier);
    pthread_mutex_destroy(&task->mutex);
}

void* releaseHydrogen(void* arg) {
    Task187* task = (Task187*)arg;
    
    sem_wait(&task->hydrogen_sem);
    pthread_mutex_lock(&task->mutex);
    task->hydrogen_count++;
    if (task->hydrogen_count == 2 && task->oxygen_count == 1) {
        task->hydrogen_count = 0;
        task->oxygen_count = 0;
        sem_post(&task->barrier);
        sem_post(&task->barrier);
        sem_post(&task->barrier);
    }
    pthread_mutex_unlock(&task->mutex);
    
    sem_wait(&task->barrier);
    printf("H");
    sem_post(&task->hydrogen_sem);
    
    return NULL;
}

void* releaseOxygen(void* arg) {
    Task187* task = (Task187*)arg;
    
    sem_wait(&task->oxygen_sem);
    pthread_mutex_lock(&task->mutex);
    task->oxygen_count++;
    if (task->hydrogen_count == 2 && task->oxygen_count == 1) {
        task->hydrogen_count = 0;
        task->oxygen_count = 0;
        sem_post(&task->barrier);
        sem_post(&task->barrier);
        sem_post(&task->barrier);
    }
    pthread_mutex_unlock(&task->mutex);
    
    sem_wait(&task->barrier);
    printf("O");
    sem_post(&task->oxygen_sem);
    
    return NULL;
}

void test_water_molecule(const char* water) {
    Task187 task;
    init_task(&task);
    
    int len = strlen(water);
    pthread_t threads[len];
    
    for (int i = 0; i < len; i++) {
        if (water[i] == 'H') {
            pthread_create(&threads[i], NULL, releaseHydrogen, &task);
        } else {
            pthread_create(&threads[i], NULL, releaseOxygen, &task);
        }
    }
    
    for (int i = 0; i < len; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\\n");
    destroy_task(&task);
}

int main() {
    const char* test_cases[] = {"HOH", "OOHHHH", "HOHHHO", "OHHHHO", "HHOHOH"};
    int num_cases = 5;
    
    for (int i = 0; i < num_cases; i++) {
        printf("Input: %s\\n", test_cases[i]);
        printf("Output: ");
        test_water_molecule(test_cases[i]);
    }
    
    return 0;
}
