#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For access, unlink
#include <sys/stat.h> // For stat

#define BUFFER_SIZE 4096 // Adjust as needed

void copyFileToTemp(const char *sourceFilePath) {
    if (sourceFilePath == NULL) {
         fprintf(stderr, "Source file path cannot be NULL.\n");
        return; 
    }
    // Check if the source file exists and is a regular file
    struct stat path_stat;
    if (stat(sourceFilePath, &path_stat) != 0 || !S_ISREG(path_stat.st_mode)) {
        fprintf(stderr, "Source file not found or not a file: %s\n", sourceFilePath);
        return;
    }



    FILE *sourceFile = fopen(sourceFilePath, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Error opening source file: %s\n", sourceFilePath);
        return; // Or exit(1) if fatal
    }


    char tempTemplate[] = "/tmp/temp_XXXXXX";
    int tempFd = mkstemp(tempTemplate); // Secure way to create temp file
    if (tempFd == -1) {
        fclose(sourceFile);
        perror("Error creating temporary file"); // Use perror for system errors
        return;
    }
    FILE *tempFile = fdopen(tempFd, "wb");
    if (tempFile == NULL) {
        fclose(sourceFile);
        close(tempFd);
        unlink(tempTemplate);
        perror("Error opening temporary file");
        return;
    }


    char buffer[BUFFER_SIZE];
    size_t bytesRead;


    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, tempFile) != bytesRead) {
            fclose(sourceFile);
            fclose(tempFile);
            unlink(tempTemplate);
            perror("Error writing to temporary file");
            return;
        }
    }


    if (ferror(sourceFile)) {
        fclose(sourceFile);
        fclose(tempFile);
        unlink(tempTemplate);
        perror("Error reading source file");
        return;
    }

    fclose(sourceFile);
    fclose(tempFile);


}

int main() {
    char testFile1[] = "test1.txt";
    char testFile2[] = "nonexistent_file.txt"; // Non-existent file
    char testDir[] = "test_dir"; // Directory, not a file
    char testFile3[] = "test3.txt"; // Non-existent file
    char testFile4[] = "abc/test4.txt"; // Path traversal
    char testFile5[] = "test5.txt"; // Non-existent file


    FILE *f = fopen(testFile1, "w");
    if (f != NULL) {
        fputs("Test file content", f);
        fclose(f);
    } else {
        perror("Error creating test file");
    }

    mkdir(testDir, 0700); // Create a directory

    copyFileToTemp(testFile1);
    printf("Copied %s successfully.\n", testFile1);



    copyFileToTemp(testFile2);


    copyFileToTemp(testDir);


    copyFileToTemp(testFile3);


    copyFileToTemp(testFile4);



    copyFileToTemp(testFile5);

    return 0;
}