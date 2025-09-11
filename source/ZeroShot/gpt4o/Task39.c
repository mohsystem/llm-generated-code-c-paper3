#include <stdio.h>
#include <stdlib.h>

char* readFileContents(const char* filename) {
    char buffer[128];
    char* result = malloc(1);
    result[0] = '\0';
    size_t len = 0;
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        return "popen() failed!";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        len += strlen(buffer);
        result = realloc(result, len + 1);
        strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
    printf("%s\n", readFileContents("testfile1.txt"));
    printf("%s\n", readFileContents("testfile2.txt"));
    printf("%s\n", readFileContents("testfile3.txt"));
    printf("%s\n", readFileContents("testfile4.txt"));
    printf("%s\n", readFileContents("testfile5.txt"));
    return 0;
}