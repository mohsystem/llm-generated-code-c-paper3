#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool uploadFile(const char *filename, const char *content) {
    char filepath[256]; // Potential buffer overflow if filename is too long.
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    // Create uploads directory if it doesn't exist
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700); // Secure permissions
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

int main() {
    // Test cases
    uploadFile("test1.txt", "Test content 1");
    uploadFile("test2.txt", "Test content 2");
    uploadFile("test3.txt", "Test content 3");
    uploadFile("test4.txt", "Test content 4");
    uploadFile("test5.txt", "Test content 5");

    return 0;
}