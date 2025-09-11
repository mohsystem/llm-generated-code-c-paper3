#include <stdio.h>
#include <stdlib.h>

void printFileContents(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file: %s\n", fileName);
    }
}

int main() {
    printFileContents("input.txt");
    return 0;
}