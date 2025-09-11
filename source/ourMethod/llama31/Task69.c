#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./task69 <filename>\n");
        return 1;
    }

    const char* filePath = argv[1];
    int result = remove(filePath);

    if (result == 0) {
        printf("File deleted successfully\n");
    } else {
        fprintf(stderr, "Failed to delete the file\n");
    }

    return 0;
}