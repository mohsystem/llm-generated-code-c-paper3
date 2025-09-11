#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define SHARED_DIRECTORY "shared_directory"

// Structure to hold file path and mutex
typedef struct {
    char filePath[256];
    pthread_mutex_t mutex;
} FileData;

// Queue implementation for file paths
typedef struct {
    FileData* data;
    int front;
    int rear;
    int size;
    int capacity;
} FileQueue;

FileQueue* createFileQueue(int capacity) {
    FileQueue* queue = (FileQueue*)malloc(sizeof(FileQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->data = (FileData*)malloc(sizeof(FileData) * capacity);
    return queue;
}

int isFull(FileQueue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(FileQueue* queue) {
    return queue->size == 0;
}

void enqueue(FileQueue* queue, const char* filePath) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    strcpy(queue->data[queue->rear].filePath, filePath);
    pthread_mutex_init(&queue->data[queue->rear].mutex, NULL);
    queue->size++;
}

FileData dequeue(FileQueue* queue) {
    FileData fileData;
    if (isEmpty(queue)) {
        strcpy(fileData.filePath, "");
        return fileData;
    }
    fileData = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return fileData;
}


void processFile(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file != NULL) {
        char line[256];
        int lineCount = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            lineCount++;
        }
        fclose(file);
        printf("Processing file: %s, Lines: %d\n", filePath, lineCount);
    } else {
        perror("Error opening file");
    }
}


void* worker(void* arg) {
    FileQueue* queue = (FileQueue*)arg;
    while (1) {
        FileData fileData = dequeue(queue);
        if (strlen(fileData.filePath) == 0) {
            break; // Queue is empty, exit thread
        }

        pthread_mutex_lock(&fileData.mutex); // Lock the file
        processFile(fileData.filePath);
        pthread_mutex_unlock(&fileData.mutex); // Unlock the file
        pthread_mutex_destroy(&fileData.mutex); // Clean up

    }
    return NULL;
}

void processFiles(const char* directory) {

    // Create shared directory if it doesn't exist
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        mkdir(directory, 0700);
    }

    FileQueue* queue = createFileQueue(1024); // Adjust capacity as needed

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Check if it's a regular file
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directory, ent->d_name);
                enqueue(queue, filePath);
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
        return;
    }


    int numThreads = sysconf(_SC_NPROCESSORS_ONLN);
    if (numThreads <= 0) {
        numThreads = 1;
    }

    pthread_t threads[numThreads];
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, worker, queue);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(queue->data);
    free(queue);
    printf("Finished processing all files.\n");
}


void createTestFiles(const char* directory, int numFiles) {
     // Delete existing files for testing purposes
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Check if it's a regular file
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directory, ent->d_name);
                remove(filePath);
            }
        }
        closedir(dir);
    }


    for (int i = 0; i < numFiles; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "file%d.txt", i);
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", directory, filename);


        FILE *file = fopen(filePath, "w");
        if (file != NULL) {
            fprintf(file, "Content of file %d", i);
            fclose(file);
        } else {
            perror("Error creating file");
        }
    }
}


int main() {
    // Test cases
    createTestFiles(SHARED_DIRECTORY, 5);
    processFiles(SHARED_DIRECTORY);

    createTestFiles(SHARED_DIRECTORY, 10);
    processFiles(SHARED_DIRECTORY);

    createTestFiles(SHARED_DIRECTORY, 1);
    processFiles(SHARED_DIRECTORY);

    createTestFiles(SHARED_DIRECTORY, 20);
    processFiles(SHARED_DIRECTORY);

    createTestFiles(SHARED_DIRECTORY, 0);