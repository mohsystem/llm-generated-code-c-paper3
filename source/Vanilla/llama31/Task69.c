#include <stdio.h>
#include <stdlib.h>

int deleteFile(const char* filePath) {
    return remove(filePath);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./Task69 <filename>\n");
        return 1;
    }
    int result = deleteFile(argv[1]);
    if (result == 0) {
        printf("%s is successfully deleted.\n", argv[1]);
    } else {
        fprintf(stderr, "File %s does not exist or could not be deleted.\n", argv[1]);
    }
    return 0;
}