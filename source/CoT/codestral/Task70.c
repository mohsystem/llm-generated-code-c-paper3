#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file path as a command line argument.\n");
        return 1;
    }
    char* fileContent = readFile(argv[1]);
    printf("%s\n", fileContent);
    free(fileContent);
    return 0;
}