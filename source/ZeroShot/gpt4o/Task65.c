#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

char* readFile(const char* filename) {
    static char buffer[1024];

    if (filename == NULL || strcmp(filename, "") == 0) {
        return "Invalid filename.";
    }

    struct stat st;
    if (stat(filename, &st) != 0 || S_ISDIR(st.st_mode)) {
        return "File does not exist or is a directory.";
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return "Error opening file.";
    }

    size_t len = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    buffer[len] = '\0';
    fclose(file);

    return buffer;
}

void testCases() {
    printf("%s\n", readFile("test1.txt"));
    printf("%s\n", readFile("test2.txt"));
    printf("%s\n", readFile(""));
    printf("%s\n", readFile("nonexistent.txt"));
    printf("%s\n", readFile(NULL));
}

int main() {
    testCases();
    return 0;
}