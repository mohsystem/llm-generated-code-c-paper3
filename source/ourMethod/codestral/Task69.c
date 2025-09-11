#include <stdio.h>
#include <stdlib.h>

int deleteFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if(file != NULL) {
        fclose(file);
        if(remove(filePath) != 0) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    return deleteFile(argv[1]);
}