#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fileExists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

char** uploadFiles(const char **filePaths, int count, int *uploadedCount) {
    char **uploadedFiles = malloc(count * sizeof(char*));
    *uploadedCount = 0;
    for (int i = 0; i < count; i++) {
        if (fileExists(filePaths[i])) {
            // Simulate file upload
            uploadedFiles[*uploadedCount] = strdup(filePaths[i]);
            (*uploadedCount)++;
        }
    }
    return uploadedFiles;
}

int main() {
    const char *files[] = {
        "path/to/file1.txt",
        "path/to/file2.txt",
        "path/to/file3.txt",
        "path/to/file4.txt",
        "path/to/file5.txt"
    };
    int uploadedCount = 0;
    char **uploadedFiles = uploadFiles(files, 5, &uploadedCount);

    printf("Uploaded Files: ");
    for (int i = 0; i < uploadedCount; i++) {
        printf("%s ", uploadedFiles[i]);
        free(uploadedFiles[i]);
    }
    free(uploadedFiles);
    printf("\n");
    return 0;
}