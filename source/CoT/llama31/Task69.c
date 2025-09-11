#include <stdio.h>
#include <stdlib.h>

int deleteFile(const char* filePath) {
    return remove(filePath) == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./task69 <file_path>\n");
        return 1;
    }
    const char* filePath = argv[1];
    if (deleteFile(filePath)) {
        printf("File deleted successfully\n");
    } else {
        fprintf(stderr, "Failed to delete the file\n");
    }
    return 0;
}