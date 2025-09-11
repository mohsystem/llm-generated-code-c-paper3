#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];
} Record;

int compare(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return strcmp(recordA->key, recordB->key);
}

void readAndSortFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    
    Record records[MAX_LINE_LENGTH];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file)) {
        char *equalsPos = strchr(line, '=');
        if (equalsPos) {
            size_t keyLength = equalsPos - line;
            strncpy(records[count].key, line, keyLength);
            records[count].key[keyLength] = '\0';
            strcpy(records[count].value, equalsPos + 1);
            records[count].value[strcspn(records[count].value, "\n")] = '\0'; // Remove newline
            count++;
        }
    }
    
    fclose(file);
    
    qsort(records, count, sizeof(Record), compare);
    
    for (int i = 0; i < count; i++) {
        printf("%s=%s\n", records[i].key, records[i].value);
    }
}

int main() {
    const char *fileName = "data.txt";
    readAndSortFile(fileName);
    return 0;
}