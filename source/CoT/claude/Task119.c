
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100
#define MAX_FIELD_LENGTH 256

typedef struct {
    char** fields;
    int count;
} CSVRow;

typedef struct {
    CSVRow* rows;
    int count;
} CSVData;

// Function to trim whitespace
char* trim(char* str) {
    char* end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\\0';
    return str;
}

// Function to safely free CSV data
void freeCSVData(CSVData* data) {
    if (data) {
        for (int i = 0; i < data->count; i++) {
            if (data->rows[i].fields) {
                for (int j = 0; j < data->rows[i].count; j++) {
                    free(data->rows[i].fields[j]);
                }
                free(data->rows[i].fields);
            }
        }
        free(data->rows);
    }
}

CSVData* parseCSV(const char* filePath) {
    if (!filePath || strlen(filePath) == 0) {
        printf("Error: File path cannot be null or empty\\n");
        return NULL;
    }

    // Check file extension
    const char* ext = strrchr(filePath, '.');
    if (!ext || strcmp(ext, ".csv") != 0) {
        printf("Error: Invalid CSV file path\\n");
        return NULL;
    }

    FILE* file = fopen(filePath, "r");
    if (!file) {
        printf("Error: Unable to open file\\n");
        return NULL;
    }

    CSVData* data = (CSVData*)malloc(sizeof(CSVData));
    if (!data) {
        fclose(file);
        return NULL;
    }
    data->rows = NULL;
    data->count = 0;

    char line[MAX_LINE_LENGTH];
    char* fields[MAX_FIELDS];
    int allocated_rows = 10;

    data->rows = (CSVRow*)malloc(sizeof(CSVRow) * allocated_rows);
    if (!data->rows) {
        free(data);
        fclose(file);
        return NULL;
    }

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (strlen(trim(line)) == 0) continue;

        if (data->count >= allocated_rows) {
            allocated_rows *= 2;
            CSVRow* new_rows = (CSVRow*)realloc(data->rows, sizeof(CSVRow) * allocated_rows);
            if (!new_rows) {
                freeCSVData(data);
                free(data);
                fclose(file);
                return NULL;
            }
            data->rows = new_rows;
        }

        // Parse fields
        char* field = strtok(line, ",");
        int field_count = 0;

        while (field && field_count < MAX_FIELDS) {
            fields[field_count] = strdup(trim(field));
            if (!fields[field_count]) {
                for (int i = 0; i < field_count; i++) {
                    free(fields[i]);
                }
                freeCSVData(data);
                free(data);
                fclose(file);
                return NULL;
            }
            field_count++;
            field = strtok(NULL, ",");
        }

        // Allocate memory for fields in the row
        data->rows[data->count].fields = (char**)malloc(sizeof(char*) * field_count);
        if (!data->rows[data->count].fields) {
            for (int i = 0; i < field_count; i++) {
                free(fields[i]);
            }
            freeCSVData(data);
            free(data);
            fclose(file);
            return NULL;
        }

        // Copy fields to row
        for (int i = 0; i < field_count; i++) {
            data->rows[data->count].fields[i] = fields[i];
        }
        data->rows[data->count].count = field_count;
        data->count++;
    }

    fclose(file);
    return data;
}

int main() {
    // Test case 1: Normal CSV file
    FILE* file1 = fopen("test1.csv", "w");
    fprintf(file1, "name,age,city', type='text')