#include <stdio.h>
#include <stdlib.h>

char* readFileContent(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return "Error reading file: Unable to open file.";
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    
    char *content = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (content == NULL) {
        fclose(file);
        return "Error reading file: Memory allocation failed.";
    }
    
    size_t readSize = fread(content, sizeof(char), fileSize, file);
    content[readSize] = '\0';
    
    fclose(file);
    return content;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            char *filePath = argv[i];
            printf("Content of %s:\n", filePath);
            char *content = readFileContent(filePath);
            printf("%s\n", content);
            free(content);
        }
    } else {
        printf("No file path provided.\n");
    }
    return 0;
}