
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000

typedef struct {
    char* key;
    char* value;
} KeyValue;

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return strcmp(((KeyValue*)a)->key, ((KeyValue*)b)->key);
}

KeyValue* readAndSortRecords(const char* filename, int* recordCount) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\\n", filename);
        *recordCount = 0;
        return NULL;
    }
    
    KeyValue* records = malloc(MAX_RECORDS * sizeof(KeyValue));
    if (!records) {
        fclose(file);
        *recordCount = 0;
        return NULL;
    }
    
    char line[MAX_LINE];
    int count = 0;
    
    while (fgets(line, MAX_LINE, file) && count < MAX_RECORDS) {
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\\0';
            // Allocate and copy key
            records[count].key = strdup(line);
            // Allocate and copy value (remove newline if present)
            char* value = equals + 1;
            char* newline = strchr(value, '\\n');
            if (newline) *newline = '\\0';
            records[count].value = strdup(value);
            count++;
        }
    }
    
    fclose(file);
    
    // Sort records
    qsort(records, count, sizeof(KeyValue), compare);
    
    *recordCount = count;
    return records;
}

void freeRecords(KeyValue* records, int count) {
    if (records) {
        for (int i = 0; i < count; i++) {
            free(records[i].key);
            free(records[i].value);
        }
        free(records);
    }
}

int main() {
    const char* testFiles[] = {
        "test1.txt",  // Normal case with multiple records
        "test2.txt",  // Empty file
        "test3.txt",  // File with single record
        "test4.txt",  // File with duplicate keys
        "test5.txt"   // File with invalid format
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", testFiles[i]);
        int recordCount;
        KeyValue* records = readAndSortRecords(testFiles[i], &recordCount);
        
        if (records) {
            for (int j = 0; j < recordCount; j++) {
                printf("%s=%s\\n", records[j].key, records[j].value);
            }
            freeRecords(records, recordCount);
        }
        printf("\\n");
    }
    
    return 0;
}
