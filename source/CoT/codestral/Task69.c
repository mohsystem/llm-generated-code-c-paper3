#include <stdio.h>
#include <stdlib.h>

int deleteFile(const char* filePath) {
    if (remove(filePath) == 0) {
        printf("File deleted successfully\n");
        return 0;
    } else {
        perror("Error deleting file");
        return 1;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file path\n");
        return 1;
    }
    return deleteFile(argv[1]);
}