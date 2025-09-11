#include <stdio.h>
#include <stdlib.h>

char** number(const char *lines[], int size, int *newSize) {
    char **numberedLines = malloc(size * sizeof(char*));
    *newSize = size;
    for(int i = 0; i < size; i++) {
        char buffer[10];
        sprintf(buffer, "%d: ", i + 1);
        int bufferSize = strlen(buffer);
        int lineSize = strlen(lines[i]);
        char *numberedLine = malloc((bufferSize + lineSize + 1) * sizeof(char));
        strcpy(numberedLine, buffer);
        strcpy(numberedLine + bufferSize, lines[i]);
        numberedLines[i] = numberedLine;
    }
    return numberedLines;
}

int main() {
    const char *test[] = {"a", "b", "c"};
    int size;
    char **result = number(test, 3, &size);
    for(int i = 0; i < size; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}