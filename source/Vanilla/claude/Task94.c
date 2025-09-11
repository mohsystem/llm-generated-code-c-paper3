
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_PAIRS 1000

typedef struct {
    char key[MAX_LINE];
    char value[MAX_LINE];
} KeyValue;

int compare(const void* a, const void* b) {
    return strcmp(((KeyValue*)a)->key, ((KeyValue*)b)->key);
}

KeyValue* sortKeyValueFile(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    KeyValue* pairs = malloc(MAX_PAIRS * sizeof(KeyValue));
    char line[MAX_LINE];
    *count = 0;
    
    while (fgets(line, MAX_LINE, file) && *count < MAX_PAIRS) {
        char* colon = strchr(line, ':');
        if (colon) {
            *colon = '\\0';
            strcpy(pairs[*count].key, line);
            strcpy(pairs[*count].value, colon + 1);
            // Remove newline if present
            char* newline = strchr(pairs[*count].value, '\\n');
            if (newline) *newline = '\\0';
            (*count)++;
        }
    }
    
    fclose(file);
    qsort(pairs, *count, sizeof(KeyValue), compare);
    return pairs;
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    const char* testData[][3] = {
        {"key1:value1", "key2:value2", "key3:value3"},
        {"banana:yellow", "apple:red", "cherry:red"},
        {"z:26", "y:25", "x:24"},
        {"name:john", "age:30", "city:nyc"},
        {"1:one", "2:two", "3:three"}
    };
    
    for(int i = 0; i < 5; i++) {
        FILE* file = fopen(testFiles[i], "w");
        for(int j = 0; j < 3; j++) {
            fprintf(file, "%s\\n", testData[i][j]);
        }
        fclose(file);
        
        printf("Test case %d:\\n", i+1);
        int count;
        KeyValue* result = sortKeyValueFile(testFiles[i], &count);
        if (result) {
            for(int j = 0; j < count; j++) {
                printf("%s:%s\\n", result[j].key, result[j].value);
            }
            free(result);
        }
        printf("\\n");
    }
    
    return 0;
}
