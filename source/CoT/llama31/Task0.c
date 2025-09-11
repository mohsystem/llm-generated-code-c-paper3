#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* processFile(void* arg) {
    char* filePath = (char*)arg;
    pthread_mutex_lock(&mtx);
    // Simulate file processing
    printf("Processing file: %s\n", filePath);
    FILE* outputFile = fopen(strcat(filePath, ".processed"), "w");
    if (outputFile == NULL) {
        perror("Error opening file");
    } else {
        fprintf(outputFile, "File processed successfully");
        fclose(outputFile);
    }
    pthread_mutex_unlock(&mtx);
    free(filePath);
    return NULL;
}

int main() {
    DIR* dir;
    struct dirent* ent;
    pthread_t threads[100]; // Adjust the size as needed
    int threadCount = 0;

    dir = opendir("/path/to/shared/directory");
    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) {
            char* filePath = malloc(strlen(ent->d_name) + strlen("/path/to/shared/directory/") + 1);
            sprintf(filePath, "/path/to/shared/directory/%s", ent->d_name);
            pthread_create(&threads[threadCount++], NULL, processFile, filePath);
        }
    }

    closedir(dir);

    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mtx);

    return 0;
}