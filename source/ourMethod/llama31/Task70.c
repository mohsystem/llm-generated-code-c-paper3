#include <stdio.h>
#include <stdlib.h>

void read_file_content(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found: %s\n", file_path);
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char* content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }
    fread(content, sizeof(char), file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    fclose(file);
    printf("%s", content);
    free(content);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    read_file_content(argv[1]);
    return 0;
}