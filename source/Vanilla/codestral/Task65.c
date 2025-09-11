#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 256

char* readFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
        return NULL;
    }
    char* buffer = malloc(BUF_SIZE);
    if (!buffer) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(file);
        return NULL;
    }
    size_t len = 0;
    char* line = NULL;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        strcat(buffer, line);
    }
    free(line);
    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide a filename as a command line argument.\n");
        return 1;
    }
    char* fileContent = readFile(argv[1]);
    if (fileContent) {
        printf("%s\n", fileContent);
        free(fileContent);
    }
    return 0;
}