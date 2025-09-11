#include <stdio.h>
#include <stdlib.h>

int deleteFile(const char* filePath) {
    if (remove(filePath) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file path as an argument.\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        const char* filePath = argv[i];
        int isDeleted = deleteFile(filePath);
        if (isDeleted) {
            printf("File deleted successfully: %s\n", filePath);
        } else {
            printf("Failed to delete file: %s\n", filePath);
        }
    }

    return 0;
}