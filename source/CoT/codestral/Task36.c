#include <stdio.h>

void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file: %s\n", filename);
    }
}

int main() {
    readFile("test.txt");
    return 0;
}