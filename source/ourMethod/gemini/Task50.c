#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // For access function
#include <libgen.h> // For dirname function

char* uploadFile(const char* uploadDirectory, const char* fileName, const char* fileData, size_t dataSize) {
    // Create upload directory if it doesn't exist
    char* dirCopy = strdup(uploadDirectory); // Make a copy for dirname
    if (access(uploadDirectory, F_OK) != 0) { // Check if directory exists
        if (mkdir(uploadDirectory, 0777) != 0 && errno != EEXIST) { // Create if doesn't exist and not created by race condition
            char* errorMessage = (char*)malloc(100 * sizeof(char));
            snprintf(errorMessage, 100, "Error creating directory: %s", uploadDirectory);
            free(dirCopy);
            return errorMessage;
        }
    } else if (access(uploadDirectory, W_OK) != 0) {
        char* errorMessage = (char*)malloc(100 * sizeof(char));
        snprintf(errorMessage, 100, "No write access to directory: %s", uploadDirectory);
        free(dirCopy);
        return errorMessage;
    }
    free(dirCopy);

    // Specify the file path
    char* filePath = (char*)malloc((strlen(uploadDirectory) + strlen(fileName) + 2) * sizeof(char));
    sprintf(filePath, "%s/%s", uploadDirectory, fileName);


    // Write file data to the specified path
    FILE* file = fopen(filePath, "wb");
    if (file == NULL) {
        char* errorMessage = (char*)malloc(100 * sizeof(char));
        snprintf(errorMessage, 100, "Error opening file for writing: %s", filePath);
        free(filePath);
        return errorMessage;
    }
    fwrite(fileData, 1, dataSize, file);
    fclose(file);

    free(filePath);
    char* successMessage = strdup("File uploaded successfully!");
    return successMessage;
}

int main() {
    const char* uploadDir = "uploads";

    // Test cases
    char* result;

    result = uploadFile(uploadDir, "test1.txt", "Test file 1 content", strlen("Test file 1 content"));
    printf("%s\n", result);
    free(result);

    result = uploadFile(uploadDir, "test2.pdf", "Test PDF content", strlen("Test PDF content"));
    printf("%s\n", result);
    free(result);
    
    result = uploadFile(uploadDir, "report.docx", "Word document content", strlen("Word document content"));
    printf("%s\n", result);
    free(result);

    result = uploadFile(uploadDir, "image.png", "Image data", strlen("Image data"));
    printf("%s\n", result);
    free(result);
    
    result = uploadFile(uploadDir, "test_with_special_chars_<>&\"'.txt", "Test with special characters", strlen("Test with special characters"));
    printf("%s\n", result);
    free(result);

    return 0;
}