#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep
#include <string.h>
#include <dirent.h> // For directory operations
#include <sys/stat.h> // For mkdir

#define SHARED_DIRECTORY "shared_directory"

pthread_mutex_t file_mutex;

void process_file(const char *file_path) {
    pthread_mutex_lock(&file_mutex);
    FILE *file = fopen(file_path, "r");
    if (file != NULL) {
        // Simulate file processing
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Process the line
        }
        sleep(1); // Simulate processing time
        printf("%lu processed: %s\n", pthread_self(), file_path);
        fclose(file);
    } else {
        perror("Error opening file");
    }
    pthread_mutex_unlock(&file_mutex);
}

int main() {
    if (mkdir(SHARED_DIRECTORY, 0777) == -1 && errno != EEXIST) {
        perror("Error creating directory");
        return 1;
    }

    // Create dummy files
    for (int i = 1; i <= 5; i++) {
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/file%d.txt", SHARED_DIRECTORY, i);
        FILE *file = fopen(file_path, "w");
        if (file != NULL) {
            fprintf(file, "Content of file %d\n", i);
            fclose(file);
        } else {
            perror("Error creating file");
        }
    }


    pthread_t threads[10]; // Adjust as needed
    int thread_count = 0;
    pthread_mutex_init(&file_mutex, NULL);

    DIR *dir = opendir(SHARED_DIRECTORY);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char file_path[256];
            snprintf(file_path, sizeof(file_path), "%s/%s", SHARED_DIRECTORY, entry->d_name);
            pthread_create(&threads[thread_count++], NULL, (void *)process_file, file_path);
        }
    }
    closedir(dir);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&file_mutex);

    printf("File processing completed.\n");
    return 0;
}