
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_RECORDS 1000

struct Record {
    char key[256];
    char value[768];
};

int compare_records(const void* a, const void* b) {
    return strcmp(((struct Record*)a)->key, ((struct Record*)b)->key);
}

void trim(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;
    
    while(*start && (*start == ' ' || *start == '\\t')) start++;
    while(end > start && (*end == ' ' || *end == '\\t' || *end == '\\n')) end--;
    
    *(end + 1) = '\\0';
    memmove(str, start, strlen(start) + 1);
}

struct Record* read_and_sort_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\\n");
        *count = 0;
        return NULL;
    }

    struct Record* records = malloc(MAX_RECORDS * sizeof(struct Record));
    if (!records) {
        fclose(file);
        *count = 0;
        return NULL;
    }

    char line[MAX_LINE];
    int record_count = 0;

    while (fgets(line, MAX_LINE, file) && record_count < MAX_RECORDS) {
        char* delimiter = strchr(line, ':');
        if (delimiter) {
            *delimiter = '\\0';
            strncpy(records[record_count].key, line, sizeof(records[record_count].key) - 1);
            strncpy(records[record_count].value, delimiter + 1, sizeof(records[record_count].value) - 1);
            
            trim(records[record_count].key);
            trim(records[record_count].value);
            
            record_count++;
        }
    }

    fclose(file);
    qsort(records, record_count, sizeof(struct Record), compare_records);
    *count = record_count;
    return records;
}

int main() {
    // Test cases
    FILE* test_file = fopen("test.txt", "w");
    if (test_file) {
        fprintf(test_file, "banana: yellow fruit\\n");
        fprintf(test_file, "apple: red fruit\\n");
        fprintf(test_file, "zebra: striped animal\\n");
        fprintf(test_file, "cat: domestic pet\\n");
        fprintf(test_file, "dog: loyal animal\\n");
        fclose(test_file);

        int count;
        struct Record* records = read_and_sort_file("test.txt", &count);
        
        if (records) {
            for (int i = 0; i < count; i++) {
                printf("%s: %s\\n", records[i].key, records[i].value);
            }
            free(records);
        }
    } else {
        printf("Error creating test file\\n");
    }

    return 0;
}
