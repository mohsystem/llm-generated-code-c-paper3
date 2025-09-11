#include <stdio.h>
#include <stdlib.h>

void readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Error: File '%s' not found.\n", filePath);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        readFile(argv[1]);
    } else {
        fprintf(stderr, "Please provide a file path as a command line argument.\n");
    }
    return 0;
}