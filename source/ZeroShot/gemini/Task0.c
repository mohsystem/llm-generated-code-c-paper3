#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>


#define SHARED_DIRECTORY "shared_directory"

pthread_mutex_t *file_mutexes; // Array of mutexes, one for each file


void process_file(char *filepath, int file_index) {

    pthread_mutex_lock(&file_mutexes[file_index]);

    printf("%lu processing %s\n", pthread_self(), filepath);
    sleep(1); // Simulate processing

    FILE *file = fopen(filepath, "r+");
    if (file == NULL) {
        perror("Error opening file");
        pthread_mutex_unlock(&file_mutexes[file_index]);

        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        pthread_mutex_unlock(&file_mutexes[file_index]);

        return;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    // Convert to uppercase
    for (int i = 0; i < file_size; i++) {
        content[i] = toupper(content[i]);
    }


    fseek(file, 0, SEEK_SET); // Rewind to the beginning
    fwrite(content, 1, strlen(content), file);
    fclose(file);
    free(content);
    pthread_mutex_unlock(&file_mutexes[file_index]);


}

int main() {
    // Create shared directory if it doesn't exist
    mkdir(SHARED_DIRECTORY, 0777);


    // Create dummy files
    for (int i = 1; i <= 5; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "%s/file%d.txt", SHARED_DIRECTORY, i);
        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "content%d", i);
            fclose(file);
        } else {
            perror("Error creating file");
            return 1;
        }
    }


     DIR *dir;
    struct dirent *ent;
    int file_count = 0;

    if ((dir = opendir(SHARED_DIRECTORY)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // Count only regular files
                file_count++;
            }
        }
        closedir(dir);
    }


    file_mutexes = (pthread_mutex_t *)malloc(file_count * sizeof(pthread_mutex_t));
    for (int i = 0; i < file_count; i++) {
        pthread_mutex_init(&file_mutexes[i], NULL);
    }

    pthread_t threads[file_count];
    int file_index = 0;
    char filepaths[file_count][100]; // Store filepaths

    if ((dir = opendir(SHARED_DIRECTORY)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                snprintf(filepaths[file_index], sizeof(filepaths[file_index]), "%s/%s", SHARED_DIRECTORY, ent->d_name);
                pthread_create(&threads[file_index], NULL, (void *(*)(void *))process_file, (void *)(filepaths[file_index], file_index));
                file_index++;

            }
        }
        closedir(dir);
    }



    for (int i = 0; i < file_count; i++) {
        pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&file_mutexes[i]); // Destroy mutexes after use
    }
    free(file_mutexes);


    printf("File processing complete.\n");

    return 0;
}