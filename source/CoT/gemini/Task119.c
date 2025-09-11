#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** parseCSV(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    char*** records = NULL;
    int recordCount = 0;
    char line[1024]; 

    while (fgets(line, sizeof(line), file)) {
        recordCount++;
        records = realloc(records, recordCount * sizeof(char**));
        if (!records) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return NULL; // or handle error differently
        }

        records[recordCount - 1] = NULL;
        int valueCount = 0;
        char* token = strtok(line, ",");
        while (token) {
            valueCount++;
            records[recordCount - 1] = realloc(records[recordCount - 1], valueCount * sizeof(char*));

            if (!records[recordCount - 1]) {
                fprintf(stderr, "Memory allocation error\n");
                fclose(file);
                // Free previously allocated memory
                return NULL;
            }

            records[recordCount - 1][valueCount - 1] = strdup(token);
                if (!records[recordCount - 1][valueCount - 1]) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }



            token = strtok(NULL, ",");

             // Remove trailing newline from the last token
            if (!token) {
              size_t len = strlen(records[recordCount - 1][valueCount - 1]);
              if (len > 0 && records[recordCount - 1][valueCount - 1][len - 1] == '\n') {
                   records[recordCount - 1][valueCount - 1][len - 1] = '\0';
              }
             }
        }
    }
    fclose(file);
    return records;
}


int main() {
    char* filePaths[] = {"test1.csv", "test2.csv", "test3.csv", "test4.csv", "test5.csv"};
    int numFiles = sizeof(filePaths) / sizeof(filePaths[0]);

    for (int i = 0; i < numFiles; i++) {
        char*** data = parseCSV(filePaths[i]);
         if (data) {

            for (int j = 0; data[j] != NULL; j++) {
                for (int k = 0; data[j][k] != NULL; k++) {
                    printf("%s ", data[j][k]);
                    free(data[j][k]);
                }

                free(data[j]);
                printf("\n");

            }
            free(data);

        }
    }

    return 0;
}