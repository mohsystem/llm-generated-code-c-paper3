#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096

char* readFileContent(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        char *error_message = (char*)malloc(256);
        snprintf(error_message, 256, "Error: %s", strerror(errno));
        return error_message;
    }

    char *content = (char*)malloc(BUFFER_SIZE);
    if (!content) {
        fclose(file);
        return "Error: Memory allocation failed.";
    }

    size_t total_read = 0;
    size_t read_size;
    while ((read_size = fread(content + total_read, 1, BUFFER_SIZE - total_read, file)) > 0) {
        total_read += read_size;
        if (total_read >= BUFFER_SIZE - 1) {
            break;
        }
    }
    content[total_read] = '\0';
    fclose(file);

    return content;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No file path provided.\n");
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        printf("Content of %s:\n", argv[i]);
        char *content = readFileContent(argv[i]);
        printf("%s\n", content);
        free(content);
    }

    return 0;
}