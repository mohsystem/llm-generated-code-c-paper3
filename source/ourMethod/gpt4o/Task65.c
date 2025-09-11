#include <stdio.h>
#include <string.h>

char* readFile(const char* filename) {
    static char content[1024];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return "Error: Unable to open file";
    }
    size_t len = fread(content, sizeof(char), sizeof(content) - 1, file);
    content[len] = '\0';
    fclose(file);
    return content;
}

int main() {
    // Test cases
    printf("%s\n", readFile("example1.txt"));
    printf("%s\n", readFile("example2.txt"));
    printf("%s\n", readFile("invalid_path.txt"));
    printf("%s\n", readFile("example3.txt"));
    printf("%s\n", readFile("example4.txt"));
    return 0;
}