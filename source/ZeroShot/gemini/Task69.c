#include <stdio.h>
#include <stdlib.h>

// For remove() function
#include <unistd.h> 

int deleteFile(const char *filePath) {
    if (remove(filePath) == 0) {
        return 1; // Success
    } else {
        perror("Error deleting file"); // Print error message
        return 0; // Failure
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide file path as command line argument.\n");
        return 1;
    }

    const char *filePath = argv[1];

    if (deleteFile(filePath)) {
        printf("File deleted successfully.\n");
    } else {
        fprintf(stderr, "Failed to delete file.\n");  // More specific error handled within deleteFile
    }

    return 0;
}