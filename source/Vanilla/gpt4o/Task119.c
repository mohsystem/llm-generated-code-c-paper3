#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void parseCSV(const char* csvContent) {
    char* contentCopy = strdup(csvContent);
    char* line = strtok(contentCopy, "\n");

    while (line != NULL) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
        line = strtok(NULL, "\n");
    }

    free(contentCopy);
}

int main() {
    const char* csv = "name,age,city\nJohn,25,New York\nJane,30,San Francisco";
    parseCSV(csv);
    return 0;
}