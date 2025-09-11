#include <stdio.h>
#include <stdlib.h>

void deleteFile(const char* filePath) {
    if(remove(filePath) == 0) {
        printf("File deleted successfully\n");
    } else {
        printf("Unable to delete the file\n");
    }
}

int main(int argc, char* argv[]) {
    deleteFile(argv[1]); // Test with command line arguments
    return 0;
}