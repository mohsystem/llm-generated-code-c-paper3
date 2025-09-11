// C doesn't have built-in threading or semaphore libraries, so we'll use pthreads for threading and sem_t for semaphore.
// This is a simple example, error checking is not included for brevity.

#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include <stdio.h>

sem_t semaphore;

void* processFile(void* filePath) {
    sem_wait(&semaphore);
    // Process the file
    printf("Processing file: %s\n", (char*)filePath);
    // Releasing the semaphore after processing the file
    sem_post(&semaphore);
    return NULL;
}

int main() {
    DIR* directory = opendir("/path/to/directory");
    struct dirent* entry;

    sem_init(&semaphore, 0, 1);

    while ((entry = readdir(directory)) != NULL) {
        pthread_t thread;
        pthread_create(&thread, NULL, processFile, entry->d_name);
        pthread_detach(thread);
    }

    closedir(directory);
    sem_destroy(&semaphore);

    return 0;
}