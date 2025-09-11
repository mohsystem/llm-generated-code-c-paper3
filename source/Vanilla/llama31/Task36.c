#include <stdio.h>
#include <stdlib.h>

void readAndPrintFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("An error occurred: File not found.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main() {
    const char* testCases[] = {"filename1.txt", "filename2.txt", "filename3.txt", "filename4.txt", "filename5.txt"};
    for (int i = 0; i < 5; i++) {
        readAndPrintFile(testCases[i]);
    }
    return 0;
}