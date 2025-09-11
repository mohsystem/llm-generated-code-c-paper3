#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* processFile(void* filePath) {
    pthread_mutex_lock(&lock);
    // Simulate file processing
    printf("Processing file: %s\n", (char*)filePath);
    FILE* file = fopen((char*)filePath, "a");
    if (file != NULL) {
        fprintf(file, "Processed by thread: %lu\n", (unsigned long)pthread_self());
        fclose(file);
    } else {
        perror("Unable to open file");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    DIR* dir;
    struct dirent* ent;
    char directoryPath[] = "/path/to/shared/directory";
    pthread_t threads[100];
    int threadCount = 0;

    if ((dir = opendir(directoryPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                pthread_create(&threads[threadCount], NULL, processFile, filePath);
                threadCount++;
            }
        }
        closedir(dir);
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}