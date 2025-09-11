#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_KEY_VALUE_LENGTH 100

typedef struct {
    char key[MAX_KEY_VALUE_LENGTH];
    char value[MAX_KEY_VALUE_LENGTH];
} Record;

int compare_records(const void *a, const void *b) {
    return strcmp(((Record *)a)->key, ((Record *)b)->key);
}

Record* sort_records(const char *file_path, int *num_records) {
    Record *records = (Record *)malloc(MAX_RECORDS * sizeof(Record));
    *num_records = 0;

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char line[MAX_KEY_VALUE_LENGTH * 2];
    while (fgets(line, sizeof(line), file) != NULL && *num_records < MAX_RECORDS) {
        char *key = strtok(line, " \t\n");
        char *value = strtok(NULL, "\n"); 

        if (key != NULL && value != NULL) {
            strcpy(records[*num_records].key, key);
            strcpy(records[*num_records].value, value);
            (*num_records)++;
        }
    }

    fclose(file);
    qsort(records, *num_records, sizeof(Record), compare_records);
    return records;

}

int main() {
    int num_records;
    Record *records;


    for (int i = 1; i <= 5; i++) {
        char file_path[20]; // Adjust size as needed
        snprintf(file_path, sizeof(file_path), "test%d.txt", i); 

        records = sort_records(file_path, &num_records);
        if (records != NULL) {
            for (int j = 0; j < num_records; j++) {
                printf("%s %s\n", records[j].key, records[j].value);
            }
            free(records);
            printf("\n"); // Add newline for separation
        }
    }

    return 0;
}