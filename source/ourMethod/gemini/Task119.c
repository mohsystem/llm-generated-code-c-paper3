#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to parse a CSV file
//  filePath: The path to the CSV file.
// Returns a 2D array of strings, where each element represents a cell in the CSV file.
//         The function returns NULL if the file cannot be opened or if memory allocation fails.
//         The caller is responsible for freeing the returned memory.
char*** parseCSV(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return NULL;
    }

    char*** records = NULL;
    int numRecords = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        numRecords++;
        records = realloc(records, numRecords * sizeof(char**));
        if (records == NULL) {
            // Handle memory allocation failure
            fclose(file);
            return NULL; 
        }
        records[numRecords - 1] = NULL;
        int numFields = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {

            numFields++;
            records[numRecords - 1] = realloc(records[numRecords - 1], numFields * sizeof(char*));
             if (records[numRecords - 1] == NULL) {
                // Handle memory allocation failure
                fclose(file);
                return NULL; 
            }
            records[numRecords - 1][numFields - 1] = strdup(token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return records;
}


int main() {
    char* testFiles[] = { "test1.csv", "test2.csv", "test3.csv", "test4.csv", "test5.csv"};
    int numTestFiles = sizeof(testFiles) / sizeof(testFiles[0]);

    for (int i = 0; i < numTestFiles; i++) {
        printf("Test case %d:\n", i + 1);
        char*** records = parseCSV(testFiles[i]);

        if (records == NULL) {
            perror("Error parsing CSV"); // Print error from fopen or realloc
             continue;
        }

        int j = 0;
        while (records[j] != NULL) {
            int k = 0;
            while (records[j][k] != NULL) {
                printf("%s | ", records[j][k]);
                free(records[j][k]); // Free memory allocated by strdup
                k++;
            }
            printf("\n");
            free(records[j]); // Free memory allocated by realloc
            j++;
        }

        free(records); // Free memory allocated by realloc
        printf("\n");
    }

    return 0;
}