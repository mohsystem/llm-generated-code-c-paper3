#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        char* error = malloc(100 * sizeof(char));
        sprintf(error, "Error: %s", strerror(errno));
        return error;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc((size + 1) * sizeof(char));
    fread(buffer, size, 1, file);
    fclose(file);

    buffer[size] = '\0';
    return buffer;
}

int main() {
    printf("%s\n", readFile("test.txt"));
    printf("%s\n", readFile("nonexistent.txt"));
    printf("%s\n", readFile(""));
    printf("%s\n", readFile("inaccessible.txt"));
    printf("%s\n", readFile("directory/"));
    return 0;
}