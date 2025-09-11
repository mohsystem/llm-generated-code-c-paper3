#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int fileExists(const char *filePath) {
    struct stat buffer;
    return (stat(filePath, &buffer) == 0);
}

int deleteFile(const char *filePath) {
    if (!fileExists(filePath)) {
        printf("File does not exist: %s\n", filePath);
        return 0;
    }
    return remove(filePath) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Please provide exactly 5 file paths.\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        printf("%s %s\n", deleteFile(argv[i]) ? "File deleted:" : "Failed to delete:", argv[i]);
    }

    return 0;
}