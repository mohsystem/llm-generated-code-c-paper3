#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 100

void parseCSV(const char* filename, char*** records, int* numRecords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    *numRecords = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        (*numRecords)++;
        char** tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));
        char* token = strtok(line, ",");
        int numTokens = 0;
        while (token != NULL) {
            tokens[numTokens] = (char*)malloc(strlen(token) + 1);
            strcpy(tokens[numTokens], token);

            // Remove leading and trailing whitespaces
            char* start = tokens[numTokens];
            char* end = start + strlen(tokens[numTokens]) - 1;
            while (isspace(*start)) start++;
            while (isspace(*end) && end >= start) end--;
            *(end + 1) = '\0';

            numTokens++;
            token = strtok(NULL, ",");
        }
        records[*numRecords - 1] = tokens;
    }

    fclose(file);
}

int main() {
    char** records[MAX_TOKENS];
    int numRecords;
    parseCSV("example.csv", records, &numRecords);
    for (int i = 0; i < numRecords; i++) {
        char** record = records[i];
        int j = 0;
        while (record[j] != NULL) {
            printf("%s ", record[j]);
            j++;
        }
        printf("\n");
    }
    return 0;
}