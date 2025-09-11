
// Note: C doesn't have built-in support for threading and concurrent processing
// This is a simplified version using POSIX threads (pthread)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_FILES 100
#define MAX_PATH 256
#define NUM_THREADS 3

typedef struct {
    char filepath[MAX_PATH];
    pthread_mutex_t* lock;
} FileTask;

typedef struct {
    FileTask* tasks;
    int start;
    int end;
} ThreadArgs;

pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_mutexes[MAX_FILES];

void process_file(const char* filepath, pthread_mutex_t* lock) {
    pthread_mutex_lock(lock);
    
    FILE* file = fopen(filepath, "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            // Process each line
            printf("Thread %lu processing file: %s - %s", 
                   (unsigned long)pthread_self(), filepath, line);
            usleep(100000); // Simulate processing time (100ms)
        }
        fclose(file);
    }
    
    pthread_mutex_unlock(lock);
}

void* thread_function(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    for (int i = args->start; i < args->end; i++) {
        process_file(args->tasks[i].filepath, args->tasks[i].lock);
    }
    
    return NULL;
}

int main() {
    // Create test directory
    mkdir("test_files", 0777);
    
    // Create test files
    for (int i = 1; i <= 5; i++) {
        char filepath[MAX_PATH];
        snprintf(filepath, sizeof(filepath), "test_files/file%d.txt", i);
        FILE* file = fopen(filepath, "w");
        if (file != NULL) {
            fprintf(file, "Test content %d\\n", i);
            fclose(file);
        }
    }
    
    // Initialize file tasks
    FileTask tasks[MAX_FILES];
    int task_count = 0;
    
    DIR* dir = opendir("test_files");
    if (dir != NULL) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {  // Regular file
                snprintf(tasks[task_count].filepath, MAX_PATH, 
                        "test_files/%s", entry->d_name);
                tasks[task_count].lock = &file_mutexes[task_count];
                pthread_mutex_init(tasks[task_count].lock, NULL);
                task_count++;
            }
        }
        closedir(dir);
    }
    
    // Create threads
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int files_per_thread = (task_count + NUM_THREADS - 1) / NUM_THREADS;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].tasks = tasks;
        thread_args[i].start = i * files_per_thread;
        thread_args[i].end = (i + 1) * files_per_thread;
        if (thread_args[i].end > task_count) {
            thread_args[i].end = task_count;
        }
        
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    
    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Cleanup
    for (int i = 0; i < task_count; i++) {
        pthread_mutex_destroy(&file_mutexes[i]);
    }
    pthread_mutex_destroy(&global_mutex);
    
    return 0;
}
