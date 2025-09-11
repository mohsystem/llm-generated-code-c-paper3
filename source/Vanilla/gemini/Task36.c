#include <stdio.h>
#include <stdlib.h>

void printFileContents(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found: %s\n", filePath);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    printFileContents("test1.txt");
    printFileContents("test2.txt");
    printFileContents("test3.txt");
    printFileContents("test4.txt");
    printFileContents("test5.txt");
    return 0;
}