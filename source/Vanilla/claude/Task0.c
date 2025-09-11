
// C doesn't have built-in support for threading in the standard library\n// You would need to use platform-specific threading libraries like pthread\n// or Windows threads. Here's a basic example using pthread:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FILES 10
#define MAX_FILENAME 256
#define DIRECTORY "./files/"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char in_process_files[MAX_FILES][MAX_FILENAME];
int in_process_count = 0;

typedef struct {
    char filename[MAX_FILENAME];
} ThreadArgs;

int is_file_in_process(const char* filename) {
    for(int i = 0; i < in_process_count; i++) {
        if(strcmp(in_process_files[i], filename) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_file_to_process(const char* filename) {
    if(in_process_count < MAX_FILES) {
        strcpy(in_process_files[in_process_count++], filename);
    }
}

void remove_file_from_process(const char* filename) {
    for(int i = 0; i < in_process_count; i++) {
        if(strcmp(in_process_files[i], filename) == 0) {
            for(int j = i; j < in_process_count - 1; j++) {
                strcpy(in_process_files[j], in_process_files[j + 1]);
            }
            in_process_count--;
            break;
        }
    }
}

void* process_file(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    pthread_mutex_lock(&mutex);
    if(is_file_in_process(args->filename)) {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    add_file_to_process(args->filename);
    pthread_mutex_unlock(&mutex);
    
    printf("Thread processing file: %s\\n", args->filename);
    sleep(1); // Simulate processing
    
    char full_path[MAX_FILENAME * 2];
    sprintf(full_path, "%s%s", DIRECTORY, args->filename);
    
    FILE* file = fopen(full_path, "r");
    if(file != NULL) {
        char line[256];
        while(fgets(line, sizeof(line), file)) {
            printf("Thread reading: %s", line);
        }
        fclose(file);
    }
    
    pthread_mutex_lock(&mutex);
    remove_file_from_process(args->filename);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void process_files(char** filenames, int count) {
    pthread_t threads[MAX_FILES];
    ThreadArgs args[MAX_FILES];
    
    for(int i = 0; i < count; i++) {
        strcpy(args[i].filename, filenames[i]);
        pthread_create(&threads[i], NULL, process_file, &args[i]);
    }
    
    for(int i = 0; i < count; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    // Test cases
    char* test_case1[] = {"file1.txt", "file2.txt", "file3.txt"};
    char* test_case2[] = {"file1.txt", "file1.txt"};
    char* test_case3[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    char* test_case4[] = {"nonexistent.txt"};
    char* test_case5[] = {"file1.txt", "file2.txt"};
    
    printf("\\nTest case 1:\\n");
    process_files(test_case1, 3);
    sleep(2);
    
    printf("\\nTest case 2:\\n");
    process_files(test_case2, 2);
    sleep(2);
    
    printf("\\nTest case 3:\\n");
    process_files(test_case3, 5);
    sleep(2);
    
    printf("\\nTest case 4:\\n");
    process_files(test_case4, 1);
    sleep(2);
    
    printf("\\nTest case 5:\\n");
    process_files(test_case5, 2);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
