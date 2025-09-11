#include <stdio.h>

int deleteFile(const char *filePath) {
    return remove(filePath) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file path.\n");
        return 1;
    }

    const char *filePath = argv[1];
    int result = deleteFile(filePath);
    printf("File deleted: %s\n", result ? "true" : "false");
    return 0;
}