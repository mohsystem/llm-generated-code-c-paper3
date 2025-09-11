#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void parseCSV(const char *csvContent) {
    char *contentCopy = strdup(csvContent);
    char *line = strtok(contentCopy, "\n");

    while (line) {
        char *record = strdup(line);
        char *cell = strtok(record, ",");
        
        while (cell) {
            printf("%s ", cell);
            cell = strtok(NULL, ",");
        }
        printf("\n");
        
        free(record);
        line = strtok(NULL, "\n");
    }
    
    free(contentCopy);
}

int main() {
    const char *csvContent = "name,age,city\nAlice,30,New York\nBob,25,Los Angeles\nCharlie,35,Chicago";
    parseCSV(csvContent);
    return 0;
}