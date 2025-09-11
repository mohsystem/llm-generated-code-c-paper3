
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_FILES 100
#define MAX_PATH 256

typedef struct {
    char filename[MAX_PATH];
    pthread_mutex_t lock;
    int in_use;
} file_entry;

typedef struct {
    file_entry files[MAX_FILES];
    int file_count;
    char directory[MAX_PATH];
    pthread_mutex_t files_mutex;
} Task0;

Task0* create_processor(const char* dir_path) {
    Task0* processor = (Task0*)malloc(sizeof(Task0));
    if (!processor) return NULL;
    
    memset(processor, 0, sizeof(Task0));
    strncpy(processor->directory, dir_path, MAX_PATH-1);
    pthread_mutex_init(&processor->files_mutex, NULL);
    
    // Create directory if it doesn't exist
    mkdir(dir_path, 0755);
    
    return processor;
}

void destroy_processor(Task0* processor) {
    if (processor) {
        pthread_mutex_destroy(&processor->files_mutex);
        free(processor);
    }
}

void* process_file(void* arg) {
    Task0* processor = (Task0*)arg;
    int processed = 0;
    
    pthread_mutex_lock(&processor->files_mutex);
    
    for (int i = 0; i < processor->file_count; i++) {
        if (!processor->files[i].in_use) {
            processor->files[i].in_use = 1;
            processed = 1;
            
            printf("Processing file: %s by thread: %lu\\n", 
                   processor->files[i].filename, 
                   (unsigned long)pthread_self());
            
            // Simulate file processing
            pthread_mutex_unlock(&processor->files_mutex);
            sleep(1);
            pthread_mutex_lock(&processor->files_mutex);
            
            processor->files[i].in_use = 0;
            break;
        }
    }
    
    pthread_mutex_unlock(&processor->files_mutex);
    
    return NULL;
}

void process_files(Task0* processor, int num_threads) {
    if (!processor) return;
    
    // Scan directory for files
    DIR* dir = opendir(processor->directory);
    if (!dir) return;
    
    struct dirent* entry;
    processor->file_count = 0;
    
    while ((entry = readdir(dir)) != NULL && processor->file_count < MAX_FILES) {
        if (entry->d_type == DT_REG) {  // Regular file
            strncpy(processor->files[processor->file_count].filename, 
                    entry->d_name, 
                    MAX_PATH-1);
            pthread_mutex_init(&processor->files[processor->file_count].lock, NULL);
            processor->files[processor->file_count].in_use = 0;
            processor->file_count++;
        }
    }
    closedir(dir);
    
    // Create and start threads
    pthread_t threads[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, process_file, processor);
    }
    
    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Cleanup file locks
    for (int i = 0; i < processor->file_count; i++) {
        pthread_mutex_destroy(&processor->files[i].lock);
    }
}

int main() {
    // Test cases
    const char* test_dir = "test_files";
    Task0* processor = create_processor(test_dir);
    
    if (!processor) {
        printf("Failed to create processor\\n");
        return 1;
    }
    
    // Create test files
    char filepath[MAX_PATH];
    for (int i = 1; i <= 5; i++) {
        snprintf(filepath, MAX_PATH, "%s/file%d.txt", test_dir, i);
        FILE* f = fopen(filepath, "w");
        if (f) {
            fprintf(f, "Test content %d", i);
            fclose(f);
        }
    }
    
    // Test with different numbers of threads
    process_files(processor, 2);
    process_files(processor, 3);
    process_files(processor, 4);
    process_files(processor, 5);
    process_files(processor, 1);
    
    destroy_processor(processor);
    
    return 0;
}
