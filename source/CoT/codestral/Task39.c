#include <stdio.h>

void displayFileContents(const char* filename) {
    FILE* file = fopen(filename, "r");
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
    displayFileContents("test.txt");
    return 0;
}