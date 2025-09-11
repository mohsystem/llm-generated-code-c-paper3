#include <stdio.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MAX_THREADS 10

pthread_mutex_t directory_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_locks[MAX_THREADS];
char *files[MAX_THREADS];
int file_count = 0;

void *process_file(void *arg) {
    int index = *((int *)arg);
    pthread_mutex_lock(&file_locks[index]);
    printf("Processing file: %s\n", files[index]);
    sleep(1);
    pthread_mutex_unlock(&file_locks[index]);
    return NULL;
}

void process_directory(const char *directory_path) {
    DIR *d = opendir(directory_path);
    struct dirent *dir;
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                pthread_mutex_lock(&directory_lock);
                files[file_count] = strdup(dir->d_name);
                pthread_mutex_init(&file_locks[file_count], NULL);
                int *arg = malloc(sizeof(*arg));
                *arg = file_count;
                pthread_create(&threads[thread_count++], NULL, process_file, arg);
                file_count++;
                pthread_mutex_unlock(&directory_lock);
            }
        }
        closedir(d);

        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

int main() {
    process_directory("test_directory");
    return 0;
}