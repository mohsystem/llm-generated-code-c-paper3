#include <stdio.h>

void printFileContents(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Unable to open file\n");
    }
}

int main() {
    printFileContents("test.txt");
    return 0;
}