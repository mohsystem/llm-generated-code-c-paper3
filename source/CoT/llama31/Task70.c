#include <stdio.h>
#include <stdlib.h>

void readAndPrintFileContent(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found: %s\n", filePath);
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide the file path as a command line argument.\n");
        return 1;
    }
    readAndPrintFileContent(argv[1]);

    // Test cases
    const char* testCases[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; ++i) {
        readAndPrintFileContent(testCases[i]);
    }
    return 0;
}