#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** parseCSV(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char*** records = NULL;
    int recordCount = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        recordCount++;
        records = realloc(records, recordCount * sizeof(char**));
        records[recordCount - 1] = NULL;
        int valueCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            valueCount++;
            records[recordCount - 1] = realloc(records[recordCount - 1], valueCount * sizeof(char*));
            records[recordCount - 1][valueCount - 1] = strdup(token);
            token = strtok(NULL, ",");
           
        }
         records[recordCount - 1] = realloc(records[recordCount - 1], (valueCount+1) * sizeof(char*));
           records[recordCount-1][valueCount] = NULL;
    }
     records = realloc(records, (recordCount+1) * sizeof(char**));
           records[recordCount] = NULL;


    fclose(file);
    return records;
}

int main() {
    char*** result = parseCSV("data1.csv");
        for(int i = 0; result[i]!=NULL; i++)
        {
            for(int j = 0; result[i][j]!=NULL; j++){
                printf("%s ", result[i][j]);
            }
            printf("\n");
        }

    return 0;
}