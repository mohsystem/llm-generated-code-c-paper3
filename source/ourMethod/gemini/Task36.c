#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* content = (char*)malloc(fileSize + 1); // +1 for null terminator
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(content, 1, fileSize, file);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file.\n");
        free(content);
        fclose(file);
        return NULL;
    }
    content[fileSize] = '\0'; // Null-terminate the string
    fclose(file);
    return content;
}

int main() {
    printf("Test case 1:\n");
    char* content1 = readFile("test1.txt");
    if (content1 != NULL) {
        printf("%s", content1);
        free(content1);
    }

    printf("Test case 2:\n");
    char* content2 = readFile("test2.txt");
    if (content2 != NULL) {
        printf("%s", content2);
        free(content2);
    }

    printf("Test case 3 - File not found:\n");
    char *content3 = readFile("nonexistent_file.txt");
    if (content3 != NULL) { //This will not be executed
        printf("%s", content3);
        free(content3);
    }

    printf("Test case 4 - Empty file:\n");
    char* content4 = readFile("empty.txt"); //Create an empty file for this case
    if (content4 != NULL) {
        printf("%s", content4);
        free(content4);
    }


    printf("Test case 5:\n");
    char* content5 = readFile("test3.txt"); //Create a test3.txt file for this case
    if (content5 != NULL) {
        printf("%s", content5);
        free(content5);
    }

    return 0;
}