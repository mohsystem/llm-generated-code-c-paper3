#include <stdio.h>
#include <stdlib.h>

char* readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return "Error: Cannot open file.";
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }
    fclose(file);
    return content;
}

int main() {
    printf("%s\n", readFile("example1.txt")); // Test case 1
    printf("%s\n", readFile("example2.txt")); // Test case 2
    printf("%s\n", readFile("example3.txt")); // Test case 3
    printf("%s\n", readFile("example4.txt")); // Test case 4
    printf("%s\n", readFile("example5.txt")); // Test case 5
    return 0;
}