
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define SHARED_DIR "shared_directory"
#define MAX_FILES 5
#define MAX_CONTENT 1024
#define NUM_THREADS 3

typedef struct {
    char filename[256];
    pthread_mutex_t* lock;
} FileData;

pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_locks[MAX_FILES] = {PTHREAD_MUTEX_INITIALIZER};

void* process_file(void* arg) {
    FileData* data = (FileData*)arg;
    char filepath[512];
    char content[MAX_CONTENT];
    
    snprintf(filepath, sizeof(filepath), "%s/%s", SHARED_DIR, data->filename);
    
    pthread_mutex_lock(data->lock);
    
    FILE* file = fopen(filepath, "r+");
    if (file != NULL) {
        if (fgets(content, sizeof(content), file) != NULL) {
            // Simulate processing
            usleep(100000);  // 100ms
            
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%s processed", content);
            printf("Thread %lu processed file: %s\\n", 
                   (unsigned long)pthread_self(), data->filename);
        }
        fclose(file);
    } else {
        printf("Error opening file: %s\\n", data->filename);
    }
    
    pthread_mutex_unlock(data->lock);
    return NULL;
}

void create_test_files() {
    char filepath[512];
    for (int i = 1; i <= MAX_FILES; i++) {
        snprintf(filepath, sizeof(filepath), "%s/file%d.txt", SHARED_DIR, i);
        FILE* file = fopen(filepath, "w");
        if (file != NULL) {
            fprintf(file, "Initial content %d", i);
            fclose(file);
        }
    }
}

int main() {
    pthread_t threads[MAX_FILES];
    FileData file_data[MAX_FILES];
    
    // Create directory
    #ifdef _WIN32
        mkdir(SHARED_DIR);
    #else
        mkdir(SHARED_DIR, 0777);
    #endif
    
    create_test_files();
    
    // Initialize and start threads
    for (int i = 0; i < MAX_FILES; i++) {
        snprintf(file_data[i].filename, sizeof(file_data[i].filename), 
                "file%d.txt", i + 1);
        file_data[i].lock = &file_locks[i];
        
        if (pthread_create(&threads[i], NULL, process_file, &file_data[i]) != 0) {
            printf("Error creating thread %d\\n", i);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < MAX_FILES; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
