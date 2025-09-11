#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

void* processFile(void* arg) {
    char* fileName = (char*)arg;
    pthread_mutex_lock(&lock);
    // Simulate file processing
    printf("Processing file: %s\n", fileName);
    usleep(100000); // Simulate processing delay
    pthread_mutex_unlock(&lock);
    return NULL;
}

void processFilesConcurrently(const char* directoryPath) {
    DIR* dir;
    struct dirent* entry;
    pthread_t threads[100];
    int i = 0;

    if ((dir = opendir(directoryPath)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // If the entry is a regular file
                pthread_create(&threads[i++], NULL, processFile, entry->d_name);
            }
        }
        closedir(dir);
    }

    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL);
    }
}

int main() {
    const char* directoryPath = "shared_directory_path"; // Define your shared directory path
    pthread_mutex_init(&lock, NULL);
    processFilesConcurrently(directoryPath);
    pthread_mutex_destroy(&lock);
    return 0;
}