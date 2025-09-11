#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For access, unlink


// Function to delete a file securely.
bool deleteFile(const char *filePath) {
    // Check if file exists and we have write permissions before attempting to delete.
    if (access(filePath, W_OK) == 0) {
        if (remove(filePath) == 0) {
            return true; // File deleted successfully
        } else {
            perror("Error deleting file");
            return false;
        }
    } else if (access(filePath, F_OK) != 0) {
        // File does not exist; return false but don't treat it as an error (no permission check needed)
        return false;
    } else {
        perror("Insufficient permissions to delete file");
        return false;
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide file path(s) as command-line arguments.\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (deleteFile(argv[i])) {
            printf("File deleted successfully: %s\n", argv[i]);
        } else {
            fprintf(stderr, "Failed to delete file: %s\n", argv[i]);
        }
    }

    return 0;
}