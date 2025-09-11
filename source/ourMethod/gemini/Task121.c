#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

// Function to create directories if they don't exist
bool createDirectories(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        if (mkdir(path, 0700) != 0 && errno != EEXIST) { // Use 0700 for secure permissions
            perror("mkdir failed");
            return false;
        }
    }
    return true;
}


char* uploadFile(const char *uploadDirectory, const char *fileName, const unsigned char *fileData, size_t fileSize) {
    if (!createDirectories(uploadDirectory)) {
        return NULL;
    }


    if (fileName == NULL || strlen(fileName) == 0 || strstr(fileName, "..") != NULL || strstr(fileName, "/") != NULL || strstr(fileName, "\\") != NULL) {
        fprintf(stderr, "Invalid file name.\n");
        return NULL;
    }


    size_t dirLen = strlen(uploadDirectory);
    size_t fileLen = strlen(fileName);

    char *filePath = (char *)malloc(dirLen + fileLen + 2); // +2 for '/' and null terminator
    if (filePath == NULL) {
        perror("malloc failed");
        return NULL;
    }

    strcpy(filePath, uploadDirectory);
    filePath[dirLen] = '/';
    strcpy(filePath + dirLen + 1, fileName);

    FILE *outputFile = fopen(filePath, "wb");
    if (outputFile == NULL) {
        perror("fopen failed");
        free(filePath);
        return NULL;
    }


    size_t bytesWritten = fwrite(fileData, 1, fileSize, outputFile);
    if (bytesWritten != fileSize) {
        perror("fwrite failed");
        fclose(outputFile);
        free(filePath);
        return NULL;
    }

    fclose(outputFile);
    return filePath;
}

int main() {
    const char *uploadDir = "uploads";
    unsigned char fileData[] = "Test Content";
    size_t fileSize = strlen((char *)fileData);

    char* uploadedFile = uploadFile(uploadDir, "test.txt", fileData, fileSize);

    if (uploadedFile != NULL) {
        printf("File uploaded successfully to %s\n", uploadedFile);
        free(uploadedFile); // Free allocated memory
    }


    const char *test_filenames[5] = {"file1.txt", "report.pdf", "image.jpg", "data.csv", "video.mp4"};
    for (int i = 0; i < 5; i++) {
        char *result = uploadFile(uploadDir, test_filenames[i], fileData, fileSize);
        if (result != NULL) {
            printf("%s uploaded successfully to: %s\n", test_filenames[i], result);
            free(result);
        }
    }


    return 0;
}