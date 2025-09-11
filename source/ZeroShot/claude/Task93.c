
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_RECORDS 1000

struct Record {
    char key[128];
    char value[128];
};

int compare_records(const void* a, const void* b) {
    return strcmp(((struct Record*)a)->key, ((struct Record*)b)->key);
}

struct Record* read_and_sort_records(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\\n", filename);
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
        char* colon = strchr(line, ':');
        if (colon) {
            *colon = '\\0';
            strncpy(records[record_count].key, line, 127);
            strncpy(records[record_count].value, colon + 1, 127);
            
            // Remove newline if present
            char* newline = strchr(records[record_count].value, '\\n');
            if (newline) *newline = '\\0';
            
            record_count++;
        }
    }

    fclose(file);
    qsort(records, record_count, sizeof(struct Record), compare_records);
    *count = record_count;
    return records;
}

void create_test_file(const char* filename, char** content, int content_size) {
    FILE* file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < content_size; i++) {
            fprintf(file, "%s\\n", content[i]);
        }
        fclose(file);
    }
}

int main() {
    char* test_files[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    
    char* test_contents[][3] = {
        {"key1:value1", "key2:value2", "key3:value3"},
        {"b:2", "a:1", "c:3"},
        {"name:John", "age:25", "city:NY"},
        {"1:one", "2:two", "3:three"},
        {"z:last", "x:middle", "y:end"}
    };

    for (int i = 0; i < 5; i++) {
        // Create test file
        create_test_file(test_files[i], test_contents[i], 3);

        printf("Test case %d:\\n", i + 1);
        int count;
        struct Record* sorted = read_and_sort_records(test_files[i], &count);
        
        if (sorted) {
            for (int j = 0; j < count; j++) {
                printf("%s: %s\\n", sorted[j].key, sorted[j].value);
            }
            printf("\\n");
            free(sorted);
        }

        // Clean up test file
        remove(test_files[i]);
    }

    return 0;
}
