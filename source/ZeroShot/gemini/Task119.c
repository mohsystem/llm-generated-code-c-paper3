#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** parseCSV(const char* filePath) {
    char*** records = NULL;
    int num_records = 0;

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        num_records++;
        records = realloc(records, num_records * sizeof(char**));
        records[num_records - 1] = NULL;
        int num_values = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            num_values++;
            records[num_records - 1] = realloc(records[num_records - 1], num_values * sizeof(char*));
            records[num_records - 1][num_values - 1] = strdup(token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return records;
}

int main() {
     char*** result = parseCSV("test1.csv");
    // Process and print the result as needed

    return 0;
}