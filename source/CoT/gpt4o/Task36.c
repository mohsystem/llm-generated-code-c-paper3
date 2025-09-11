#include <stdio.h>
#include <stdlib.h>

void readFileAndPrint(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        perror("Error reading the file");
    }
}

int main() {
    readFileAndPrint("test1.txt");
    readFileAndPrint("test2.txt");
    readFileAndPrint("test3.txt");
    readFileAndPrint("test4.txt");
    readFileAndPrint("test5.txt");
    return 0;
}