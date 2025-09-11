#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define DIRECTORY_PATH "shared_directory"
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void* process_file(void* arg) {
    char* file_path = (char*)arg;
    pthread_mutex_lock(&file_mutex);
    FILE* file = fopen(file_path, "r");
    if (file) {
        printf("Processing file: %s\n", strrchr(file_path, '/') + 1);
        // Simulate processing with sleep
        sleep(1);
        // Example: Read the file content
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);
        printf("Processed content of %s: %ld bytes\n", strrchr(file_path, '/') + 1, file_size);
        fclose(file);
    }
    pthread_mutex_unlock(&file_mutex);
    free(arg);
    return NULL;
}

int main() {
    struct dirent* entry;
    DIR* dir = opendir(DIRECTORY_PATH);
    if (dir == NULL) {
        return 1;
    }

    pthread_t threads[256];
    int thread_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char* file_path = malloc(strlen(DIRECTORY_PATH) + strlen(entry->d_name) + 2);
            sprintf(file_path, "%s/%s", DIRECTORY_PATH, entry->d_name);
            pthread_create(&threads[thread_count++], NULL, process_file, file_path);
        }
    }
    closedir(dir);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}