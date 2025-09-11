#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir on Linux/macOS
#include <unistd.h> // For access on Linux/macOS
#include <errno.h>
#include <libgen.h> // For dirname

#ifdef _WIN32 // For mkdir and access on Windows
#include <direct.h> // For mkdir on Windows
#include <io.h> // For access on Windows
#define access _access
#endif

// Function to create directories recursively (for handling nested directories)
int createDirectories(const char *path) {
    char *path_copy = strdup(path); // Create a copy to modify safely
    char *dir = dirname(path_copy);

    if (access(dir, 0) == -1) { // Check if directory exists
        if (createDirectories(dir) == -1) { // Recursively create parent directories
            free(path_copy);
            return -1;
        }
    }
#ifdef _WIN32
    if (_mkdir(path) == -1 && errno != EEXIST) {
#else
    if (mkdir(path, 0777) == -1 && errno != EEXIST) { // 0777 for permissions
#endif
        free(path_copy);
        return -1; // Failed to create directory
    }
    free(path_copy);
    return 0;
}


void copyFile(const char *sourcePath, const char *destPath) {
    FILE *source, *dest;
    char buffer[4096];
    size_t bytesRead;

    if (access(sourcePath, F_OK) == -1) {
        fprintf(stderr, "Source file not found: %s\n", sourcePath);
        return; // Or throw an error if you prefer exception handling
    }

    // Create destination directories if they don't exist
    char *destPathCopy = strdup(destPath); // Create a copy to avoid modifying original
    char *destDir = dirname(destPathCopy);
    if (createDirectories(destDir) == -1) {
        fprintf(stderr, "Error creating destination directory: %s\n", destDir);
        free(destPathCopy);
        return;
    }
    free(destPathCopy);


    source = fopen(sourcePath, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return;
    }

    dest = fopen(destPath, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytesRead, dest) != bytesRead) {
            perror("Error writing to destination file");
            fclose(source);
            fclose(dest);
            return;
        }
    }

    if (ferror(source)) {
        perror("Error reading from source file");
    }

    fclose(source);
    fclose(dest);
}

int main() {
    copyFile("test1.txt", "temp/test1_copy.txt");
    copyFile("test2.txt", "temp/test2_copy.txt");
    copyFile("nonexistent.txt", "temp/nonexistent_copy.txt"); // Test for file not found

    // Create temp directory if it doesn't exist
    createDirectories("temp");
    copyFile("test3.txt", "temp/test3_copy.txt"); //test for creating dest dir
    copyFile("", "temp/empty_copy.txt"); //test empty source path

    return 0;
}