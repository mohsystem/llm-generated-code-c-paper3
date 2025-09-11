#include <stdio.h>
#include <stdlib.h>

char* display_file_contents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}

int main() {
    char* contents;

    contents = display_file_contents("test1.txt");
    if (contents != NULL) {
        printf("%s", contents);
        free(contents);
    }

    contents = display_file_contents("test2.txt");
    if (contents != NULL) {
        printf("%s", contents);
        free(contents);
    }

    contents = display_file_contents("test3.txt");
    if (contents != NULL) {
        printf("%s", contents);
        free(contents);
    }

    contents = display_file_contents("test4.txt");
    if (contents != NULL) {
        printf("%s", contents);
        free(contents);
    }

    contents = display_file_contents("test5.txt");
    if (contents != NULL) {
        printf("%s", contents);
        free(contents);
    }


    return 0;
}