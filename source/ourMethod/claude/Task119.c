
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_LINE_LENGTH 4096
#define MAX_FIELDS 100
#define MAX_FIELD_LENGTH 1024

typedef struct {
    char** fields;
    size_t count;
} CSVRow;

typedef struct {
    CSVRow* rows;
    size_t count;
} CSVData;

static char* trim(char* str) {
    if (!str) return NULL;
    
    // Trim leading spaces
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return str;
    
    // Trim trailing spaces
    char* end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\\0';
    
    return str;
}

static void freeCSVData(CSVData* data) {
    if (!data) return;
    
    for (size_t i = 0; i < data->count; i++) {
        for (size_t j = 0; j < data->rows[i].count; j++) {
            free(data->rows[i].fields[j]);
        }
        free(data->rows[i].fields);
    }
    free(data->rows);
}

CSVData* parseCSV(const char* filepath) {
    if (!filepath) {
        errno = EINVAL;
        return NULL;
    }
    
    FILE* file = fopen(filepath, "r");
    if (!file) {
        return NULL;
    }
    
    CSVData* data = (CSVData*)calloc(1, sizeof(CSVData));
    if (!data) {
        fclose(file);
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    size_t capacity = 10;
    data->rows = (CSVRow*)calloc(capacity, sizeof(CSVRow));
    if (!data->rows) {
        free(data);
        fclose(file);
        return NULL;
    }
    
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\\n') {
            line[len-1] = '\\0';
        }
        
        if (strlen(trim(line)) == 0) continue;
        
        if (data->count >= capacity) {
            capacity *= 2;
            CSVRow* new_rows = (CSVRow*)realloc(data->rows, capacity * sizeof(CSVRow));
            if (!new_rows) {
                freeCSVData(data);
                free(data);
                fclose(file);
                return NULL;
            }
            data->rows = new_rows;
        }
        
        CSVRow* row = &data->rows[data->count];
        row->fields = (char**)calloc(MAX_FIELDS, sizeof(char*));
        if (!row->fields) {
            freeCSVData(data);
            free(data);
            fclose(file);
            return NULL;
        }
        
        char* token = strtok(line, ",");
        while (token && row->count < MAX_FIELDS) {
            char* trimmed = trim(token);
            row->fields[row->count] = strdup(trimmed);
            if (!row->fields[row->count]) {
                freeCSVData(data);
                free(data);
                fclose(file);
                return NULL;
            }
            row->count++;
            token = strtok(NULL, ",");
        }
        
        data->count++;
    }
    
    fclose(file);
    return data;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.csv",
        "test2.csv", 
        "test3.csv",
        "test4.csv",
        "test5.csv"
    };
    
    // Create test files
    FILE* f1 = fopen("test1.csv", "w");
    fprintf(f1, "a,b,c\\n1,2,3");
    fclose(f1);
    
    FILE* f2 = fopen("test2.csv", "w");
    fprintf(f2, "hello world,test");
    fclose(f2);
    
    FILE* f3 = fopen("test3.csv", "w");
    fclose(f3);
    
    FILE* f4 = fopen("test4.csv", "w");
    fprintf(f4, "a,b\\n\\n1,2");
    fclose(f4);
    
    FILE* f5 = fopen("test5.csv", "w");
    fprintf(f5, "quoted,value");
    fclose(f5);
    ', type='text')