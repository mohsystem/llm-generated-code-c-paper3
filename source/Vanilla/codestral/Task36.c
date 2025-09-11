#include <stdio.h>

void printFileContents(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    const char* filePath = "path_to_your_file.txt";  // replace with the path to your file
    printFileContents(filePath);
    return 0;
}