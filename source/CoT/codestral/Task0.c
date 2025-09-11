#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    char** files;
    int size;
    int capacity;
    pthread_mutex_t lock;
    sem_t sem;
} queue_t;

queue_t* createQueue() {
    queue_t* q = malloc(sizeof(queue_t));
    q->files = malloc(sizeof(char*) * 10);
    q->size = 0;
    q->capacity = 10;
    pthread_mutex_init(&q->lock, NULL);
    sem_init(&q->sem, 0, 0);
    return q;
}

void destroyQueue(queue_t* q) {
    for (int i = 0; i < q->size; i++) {
        free(q->files[i]);
    }
    free(q->files);
    pthread_mutex_destroy(&q->lock);
    sem_destroy(&q->sem);
    free(q);
}

void enqueue(queue_t* q, char* file) {
    pthread_mutex_lock(&q->lock);
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->files = realloc(q->files, sizeof(char*) * q->capacity);
    }
    q->files[q->size++] = file;
    sem_post(&q->sem);
    pthread_mutex_unlock(&q->lock);
}

char* dequeue(queue_t* q) {
    sem_wait(&q->sem);
    pthread_mutex_lock(&q->lock);
    char* file = q->files[0];
    for (int i = 1; i < q->size; i++) {
        q->files[i - 1] = q->files[i];
    }
    q->size--;
    pthread_mutex_unlock(&q->lock);
    return file;
}

void* processFile(void* arg) {
    queue_t* q = arg;
    char* file = dequeue(q);
    // process file
    free(file);
    return NULL;
}

void processFiles(const char* directory) {
    DIR* dir = opendir(directory);
    struct dirent* entry;
    queue_t* q = createQueue();
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char* file = malloc(sizeof(char) * (strlen(directory) + strlen(entry->d_name) + 2));
            sprintf(file, "%s/%s", directory, entry->d_name);
            enqueue(q, file);
        }
    }
    closedir(dir);
    while (q->size > 0) {
        pthread_t tid;
        pthread_create(&tid, NULL, processFile, q);
        pthread_detach(tid);
    }
    destroyQueue(q);
}

int main() {
    processFiles("shared_directory");
    return 0;
}