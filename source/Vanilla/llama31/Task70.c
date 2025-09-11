#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "An error occurred: Unable to open the file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        fprintf(stderr, "An error occurred: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide the file path as a command line argument.\n");
        return 1;
    }
    char* file_path = argv[1];
    char* content = read_file(file_path);
    if (content != NULL) {
        printf("%s", content);
        free(content);
    }
    return 0;
}