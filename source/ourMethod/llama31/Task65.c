#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "File not found or could not be opened: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* content = (char*)malloc(size + 1);
    if (!content) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(content, 1, size, file);
    content[size] = '\0'; // Null-terminate the string
    fclose(file);

    printf("%s", content);
    free(content);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    read_file(argv[1]);
    return 0;
}