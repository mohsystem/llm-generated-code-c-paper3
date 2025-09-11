
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024
#define MAX_FIELDS 100

void parseCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s\\n", filename);
        return;
    }

    char line[MAX_LINE_SIZE];
    char* fields[MAX_FIELDS];
    
    while (fgets(line, MAX_LINE_SIZE, file)) {
        int field_count = 0;
        char* field = strtok(line, ",\\n");
        
        while (field && field_count < MAX_FIELDS) {
            fields[field_count++] = field;
            field = strtok(NULL, ",\\n");
        }
        
        for (int i = 0; i < field_count; i++) {
            printf("%s ", fields[i]);
        }
        printf("\\n");
    }
    
    fclose(file);
}

int main() {
    const char* testFiles[] = {
        "test1.csv", // Simple CSV with numbers
        "test2.csv", // CSV with text
        "test3.csv", // CSV with mixed data
        "test4.csv", // Empty CSV
        "test5.csv"  // CSV with quoted strings
    };

    for (int i = 0; i < 5; i++) {
        printf("Processing %s:\\n", testFiles[i]);
        parseCSV(testFiles[i]);
        printf("\\n");
    }

    return 0;
}
