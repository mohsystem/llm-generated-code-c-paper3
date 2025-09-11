#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define NUM_THREADS 5
#define SHARED_DIRECTORY "shared_directory" // Replace with actual path

pthread_mutex_t file_mutex;

void *process_file(void *arg) {
    char *filepath = (char *)arg;

    // Acquire lock to ensure only one thread processes a file at a time.
    pthread_mutex_lock(&file_mutex);

    printf("Processing file: %s by thread %lu\n", filepath, pthread_self());

    // Simulate file processing - replace with your actual logic.
     // Example:
    // FILE *file = fopen(filepath, "r");
    // if (file == NULL) {
    //     perror("Error opening file");
    //     pthread_mutex_unlock(&file_mutex);
    //     return NULL;
    // }
    // // ... process the file ...
    // fclose(file);

    sleep(2); // Simulate processing time
    printf("Finished processing file: %s by thread %lu\n", filepath, pthread_self());


    pthread_mutex_unlock(&file_mutex);
    free(filepath); // Free the dynamically allocated filepath
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_count = 0;

     // Create shared directory if it doesn't exist
    struct stat st = {0};
    if (stat(SHARED_DIRECTORY, &st) == -1) {
        mkdir(SHARED_DIRECTORY, 0700);  // Create directory with permissions

        // Create dummy files for testing
        for (int i = 0; i < 10; i++) {
            char filename[256];
            snprintf(filename, sizeof(filename), "%s/file_%d.txt", SHARED_DIRECTORY, i);
            FILE *file = fopen(filename, "w");
            if (file != NULL) {
                fprintf(file, "Content of file %d\n", i);
                fclose(file);
            } else {
                perror("Error creating dummy file");
            }
        }
    }


    pthread_mutex_init(&file_mutex, NULL);

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(SHARED_DIRECTORY)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                char *filepath = (char *)malloc(strlen(SHARED_DIRECTORY) + strlen(ent->d_name) + 2); // +2 for / and \0
                sprintf(filepath, "%s/%s", SHARED_DIRECTORY, ent->d_name);

                pthread_create(&threads[thread_count++], NULL, process_file, filepath);
                if (thread_count >= NUM_THREADS) {
                  // Wait for some threads to finish before creating more
                    for(int i = 0; i < NUM_THREADS; i++) {
                        pthread_join(threads[i], NULL);
                    }
                    thread_count = 0;
                }

            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
        return 1;
    }


   // Wait for any remaining threads
    for(int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&file_mutex);

    return 0;
}