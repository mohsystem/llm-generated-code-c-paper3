
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000

struct KeyValue {
    char key[MAX_LINE];
    char value[MAX_LINE];
};

int compare(const void* a, const void* b) {
    return strcmp(((struct KeyValue*)a)->key, ((struct KeyValue*)b)->key);
}

void readAndSortFile(const char* filename, struct KeyValue* records, int* count) {
    FILE* file = fopen(filename, "r");
    char line[MAX_LINE];
    *count = 0;
    
    if (file == NULL) {
        fprintf(stderr, "Error opening file\\n");
        return;
    }
    
    while (fgets(line, sizeof(line), file) && *count < MAX_RECORDS) {
        char* equals = strchr(line, '=');
        if (equals != NULL) {
            *equals = '\\0';
            strncpy(records[*count].key, line, MAX_LINE - 1);
            strncpy(records[*count].value, equals + 1, MAX_LINE - 1);
            
            // Remove newline if present
            char* newline = strchr(records[*count].value, '\\n');
            if (newline) *newline = '\\0';
            
            (*count)++;
        }
    }
    
    fclose(file);
    qsort(records, *count, sizeof(struct KeyValue), compare);
}

int main() {
    // Test cases
    FILE* testFile = fopen("test.txt", "w");
    if (testFile != NULL) {
        fprintf(testFile, "name=John\\n");
        fprintf(testFile, "age=25\\n");
        fprintf(testFile, "city=NewYork\\n");
        fprintf(testFile, "country=USA\\n");
        fprintf(testFile, "job=Engineer\\n");
        fclose(testFile);
        
        struct KeyValue records[MAX_RECORDS];
        int count;
        readAndSortFile("test.txt", records, &count);
        
        for (int i = 0; i < count; i++) {
            printf("%s=%s\\n", records[i].key, records[i].value);
        }
    } else {
        fprintf(stderr, "Error creating test file\\n");
    }
    
    return 0;
}
