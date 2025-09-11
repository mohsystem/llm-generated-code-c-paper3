#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define DIRECTORY_PATH "shared_directory"

pthread_mutex_t lock;

void* processFile(void* filePath) {
    pthread_mutex_lock(&lock);
    char* path = (char*)filePath;
    printf("Processing file: %s\n", path);
    sleep(1);
    printf("Finished processing file: %s\n", path);
    pthread_mutex_unlock(&lock);
    free(filePath);
    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);
    DIR* d;
    struct dirent* dir;
    d = opendir(DIRECTORY_PATH);

    if (d == NULL) {
        printf("Directory does not exist or is empty\n");
        return 1;
    }

    pthread_t threads[100];
    int count = 0;

    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
            char* path = malloc(strlen(DIRECTORY_PATH) + strlen(dir->d_name) + 2);
            sprintf(path, "%s/%s", DIRECTORY_PATH, dir->d_name);
            pthread_create(&threads[count++], NULL, processFile, path);
        }
    }

    closedir(d);

    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    printf("Finished all threads\n");
    return 0;
}