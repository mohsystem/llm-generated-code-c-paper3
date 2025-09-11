
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_PAIRS 100

struct KeyValue {
    char key[MAX_LINE];
    char value[MAX_LINE];
};

int compare(const void* a, const void* b) {
    return strcmp(((struct KeyValue*)a)->key, ((struct KeyValue*)b)->key);
}

void readAndSortFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\\n", filename);
        return;
    }

    struct KeyValue pairs[MAX_PAIRS];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file) && count < MAX_PAIRS) {
        char* delimiter = strchr(line, ':');
        if (delimiter != NULL) {
            *delimiter = '\\0';
            strncpy(pairs[count].key, line, MAX_LINE - 1);
            strncpy(pairs[count].value, delimiter + 1, MAX_LINE - 1);
            
            // Remove newline if present
            char* newline = strchr(pairs[count].value, '\\n');
            if (newline) *newline = '\\0';
            
            count++;
        }
    }

    fclose(file);

    // Sort the pairs
    qsort(pairs, count, sizeof(struct KeyValue), compare);

    // Print sorted pairs
    for (int i = 0; i < count; i++) {
        printf("%s: %s\\n", pairs[i].key, pairs[i].value);
    }
    printf("\\n");
}

int main() {
    // Test cases with sample file contents
    const char* testFiles[] = {
        "test1.txt", // contains: name:John\
age:25\
city:NewYork
        "test2.txt", // contains: color:blue\
size:large\
price:100
        "test3.txt", // contains: country:USA\
state:CA\
zip:90210
        "test4.txt", // contains: fruit:apple\
vegetable:carrot\
meat:chicken
        "test5.txt"  // contains: language:Java\
version:17\
status:stable
    };

    for (int i = 0; i < 5; i++) {
        printf("Reading and sorting file: %s\\n", testFiles[i]);
        readAndSortFile(testFiles[i]);
    }

    return 0;
}
