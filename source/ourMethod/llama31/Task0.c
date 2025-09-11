#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* processFile(void* filePath) {
    pthread_mutex_lock(&mutex);
    // Process the file here
    printf("Processing file: %s\n", (char*)filePath);
    // Example: Writing to a new file
    char* processedFilePath = malloc(strlen((char*)filePath) + 10);
    strcpy(processedFilePath, "processed_");
    strcat(processedFilePath, (char*)filePath);
    FILE* writer = fopen(processedFilePath, "w");
    if (writer != NULL) {
        fprintf(writer, "File processed successfully");
        fclose(writer);
    } else {
        fprintf(stderr, "Error processing file\n");
    }
    free(processedFilePath);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    DIR* dir;
    struct dirent* ent;
    char directoryPath[] = "/path/to/shared/directory";

    dir = opendir(directoryPath);
    if (dir != NULL) {
        int numFiles = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                numFiles++;
            }
        }
        rewinddir(dir);

        pthread_t threads[numFiles];
        int fileIndex = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                pthread_create(&threads[fileIndex++], NULL, processFile, filePath);
            }
        }
        closedir(dir);

        for (int i = 0; i < numFiles; i++) {
            pthread_join(threads[i], NULL);
        }
    } else {
        perror("Could not open directory");
    }

    return 0;
}