#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';
    fclose(file);
    return fileContent;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        char* content = readFile(argv[1]);
        if (content != NULL) {
            printf("%s", content);
            free(content);
        }
    }

     char* content1 = readFile("test1.txt");
        if (content1 != NULL) {
            printf("%s", content1);
            free(content1);
        }

        char* content2 = readFile("test2.txt");
        if (content2 != NULL) {
            printf("%s", content2);
            free(content2);
        }
        char* content3 = readFile("test3.txt");
        if (content3 != NULL) {
            printf("%s", content3);
            free(content3);
        }
        char* content4 = readFile("test4.txt");
        if (content4 != NULL) {
            printf("%s", content4);
            free(content4);
        }

    return 0;
}