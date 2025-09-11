#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (remove(argv[1]) == 0) {
            printf("File deleted successfully\n");
        } else {
            printf("Failed to delete the file\n");
        }
    } else {
        printf("Please provide a file path as an argument\n");
    }
    return 0;
}