
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 10000

char* readFile(const char* filePath) {
    static char content[MAX_CONTENT_SIZE];
    FILE* file = fopen(filePath, "r");
    
    if (file == NULL) {
        snprintf(content, MAX_CONTENT_SIZE, "Error reading file: Unable to open file");
        return content;
    }
    
    size_t bytesRead = fread(content, 1, MAX_CONTENT_SIZE - 1, file);
    content[bytesRead] = '\\0';
    
    fclose(file);
    return content;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test1.txt",
        "nonexistent.txt",
        "sample.txt",
        "empty.txt",
        "data.txt"
    };
    int numFiles = 5;

    for (int i = 0; i < numFiles; i++) {
        printf("Reading file: %s\\n", testFiles[i]);
        printf("Content:\\n");
        printf("%s\\n", readFile(testFiles[i]));
        printf("------------------------\\n");
    }

    return 0;
}
