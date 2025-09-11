#include <stdio.h>
#include <stdlib.h>

char* readFileContent(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        return "Error reading file.";
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file path.\n");
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        char* content = readFileContent(argv[i]);
        if (content) {
            printf("%s\n", content);
            free(content);
        }
    }
    return 0;
}