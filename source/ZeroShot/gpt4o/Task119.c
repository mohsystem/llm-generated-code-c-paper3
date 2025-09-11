#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void parseCSV(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        while (token) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(file);
}

int main() {
    parseCSV("test.csv");
    return 0;
}