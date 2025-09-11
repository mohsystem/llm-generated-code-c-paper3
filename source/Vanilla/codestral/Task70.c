#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char* content = (char*)malloc(sizeof(char) * fileSize);
    if (content == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }
    fread(content, sizeof(char), fileSize, file);
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        fprintf(stderr, "Please provide 5 file paths as command line arguments\n");
        return 1;
    }
    char* content = readFile(argv[1]);
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }
    content = readFile(argv[2]);
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }
    content = readFile(argv[3]);
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }
    content = readFile(argv[4]);
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }
    content = readFile(argv[5]);
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }
    return 0;
}