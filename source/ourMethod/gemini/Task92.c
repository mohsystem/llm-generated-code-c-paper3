#include <stdio.h>
#include <pthread.h>

typedef struct {
    int currentCounter;
    int maxCounter;
    pthread_mutex_t lock;
} Task92;

void* incrementAndPrint(void* arg) {
    Task92* task = (Task92*)arg;
    char* threadName = (char*)((char*)arg + sizeof(Task92));

    pthread_mutex_lock(&task->lock);
    if (task->currentCounter <= task->maxCounter) {
        task->currentCounter++;
        printf("%s is accessing currentCounter: %d\n", threadName, task->currentCounter);
    }
    pthread_mutex_unlock(&task->lock);

    return NULL;
}

int main() {
    Task92 task = {0, 5, PTHREAD_MUTEX_INITIALIZER};
    pthread_t threads[5];
    char threadNames[5][10] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5"};
    char *arg[5];

    for(int i = 0; i < 5; i++) {
      arg[i] = (char*)malloc(sizeof(Task92) + sizeof(threadNames[i]));
      memcpy(arg[i], &task, sizeof(Task92));
      memcpy(arg[i] + sizeof(Task92), threadNames[i], sizeof(threadNames[i]));
      pthread_create(&threads[i], NULL, incrementAndPrint, arg[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
        free(arg[i]);
    }


    return 0;
}