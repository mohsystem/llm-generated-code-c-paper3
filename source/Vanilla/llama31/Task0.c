#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* processFile(void* arg) {
    char* filePath = (char*)arg;
    pthread_mutex_lock(&mutex);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            printf("Processing file: %s, Line: %s", filePath, line);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open file: %s\n", filePath);
    }
    pthread_mutex_unlock(&mutex);
    free(arg);
    return NULL;
}

void processFiles(const char* directoryPath) {
    DIR* dir;
    struct dirent* ent;
    pthread_t threads[100]; // Assuming max 100 files
    int threadCount = 0;

    if ((dir = opendir(directoryPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                char* filePath = malloc(strlen(directoryPath) + strlen(ent->d_name) + 2);
                sprintf(filePath, "%s/%s", directoryPath, ent->d_name);
                pthread_create(&threads[threadCount], NULL, processFile, filePath);
                threadCount++;
            }
        }
        closedir(dir);
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    const char* directoryPath = "/path/to/your/directory";
    processFiles(directoryPath);
    return 0;
}