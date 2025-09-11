#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h> // For stat() function
#include <unistd.h>  // For access(), remove() functions


bool deleteFile(const char *filePath) {

    struct stat path_stat;
    if (stat(filePath, &path_stat) != 0) {
        return false; // File does not exist or error getting status
    }


    if (S_ISDIR(path_stat.st_mode)) {
        return false; // It's a directory
    }

    if (remove(filePath) == 0) {
        return true;
    } else {
        perror("Error deleting file"); // Print error reason
        return false;
    }
}


int main(int argc, char *argv[]) {
    // Test cases
    printf("Test case 1: %s\n", deleteFile("test1.txt") ? "true" : "false");

    FILE *f = fopen("test2.txt", "w");
    if (f) fclose(f);
    printf("Test case 2: %s\n", deleteFile("test2.txt") ? "true" : "false");

    printf("Test case 3: %s\n", deleteFile("nonexistent.txt") ? "true" : "false");

    #ifdef _WIN32 // Windows-specific directory creation
        mkdir("test_dir");
    #else
        mkdir("test_dir", 0777); // Create with permissions on Unix-like systems
    #endif
    printf("Test case 4: %s\n", deleteFile("test_dir") ? "true" : "false");

    f = fopen("test3.txt", "w");
    if (f) fclose(f);
    chmod("test3.txt", S_IRUSR | S_IRGRP | S_IROTH); // Read-only permissions
    printf("Test case 5: %s\n", deleteFile("test3.txt") ? "true" : "false");


    // Cleanup (best effort)
    remove("test3.txt");
    rmdir("test_dir");

    return 0;
}