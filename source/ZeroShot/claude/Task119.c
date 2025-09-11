
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024
#define MAX_FIELDS 100

void parseCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\\n", filename);
        return;
    }

    char line[MAX_LINE_SIZE];
    char* fields[MAX_FIELDS];
    
    while (fgets(line, MAX_LINE_SIZE, file)) {
        // Remove newline
        line[strcspn(line, "\\n")] = 0;
        
        int field_count = 0;
        char* token = strtok(line, ",");
        
        while (token && field_count < MAX_FIELDS) {
            fields[field_count++] = token;
            token = strtok(NULL, ",");
        }

        // Print the fields
        for (int i = 0; i < field_count; i++) {
            printf("%s ", fields[i]);
        }
        printf("\\n");
    }
    
    fclose(file);
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test1.csv", // Simple CSV with numbers
        "test2.csv", // CSV with text data
        "test3.csv", // CSV with mixed data
        "test4.csv", // Empty CSV
        "test5.csv"  // CSV with special characters
    };

    for (int i = 0; i < 5; i++) {
        printf("Processing %s:\\n", testFiles[i]);
        parseCSV(testFiles[i]);
        printf("\\n");
    }

    return 0;
}
