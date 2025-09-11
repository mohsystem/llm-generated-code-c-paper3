
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 10000

char* readFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        char* error = malloc(100);
        sprintf(error, "Error reading file: Unable to open file");
        return error;
    }
    
    char* content = malloc(MAX_LENGTH);
    char* ptr = content;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        *ptr++ = (char)c;
    }
    *ptr = '\\0';
    
    fclose(file);
    return content;
}

int main() {
    // Test cases
    printf("Test 1: %s\\n", readFile("test1.txt"));
    printf("Test 2: %s\\n", readFile("nonexistent.txt"));
    printf("Test 3: %s\\n", readFile("empty.txt"));
    printf("Test 4: %s\\n", readFile("large.txt"));
    printf("Test 5: %s\\n", readFile("special_chars.txt"));
    
    return 0;
}
