#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void parseCSV(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }
    fclose(file);
}

int main() {
    parseCSV("test1.csv");
    parseCSV("test2.csv");
    parseCSV("test3.csv");
    parseCSV("test4.csv");
    parseCSV("test5.csv");
    return 0;
}