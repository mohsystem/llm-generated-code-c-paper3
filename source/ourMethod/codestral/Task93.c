#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_KEY_VALUE_LENGTH 128

int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

char *readFile(const char *fileName, char ***keys, char ***values, int *count) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int capacity = 10;
    *keys = malloc(capacity * sizeof(char *));
    *values = malloc(capacity * sizeof(char *));
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key != NULL && value != NULL) {
            key = strdup(key);
            value = strdup(value);

            if (key != NULL && value != NULL) {
                if (*count >= capacity) {
                    capacity *= 2;
                    *keys = realloc(*keys, capacity * sizeof(char *));
                    *values = realloc(*values, capacity * sizeof(char *));
                }

                (*keys)[*count] = key;
                (*values)[*count] = value;
                (*count)++;
            } else {
                free(key);
                free(value);
            }
        } else {
            fprintf(stderr, "Invalid line: %s\n", line);
        }
    }

    fclose(file);
    return "File read successfully.";
}

int main() {
    const char *fileName = "input.txt";
    char **keys, **values;
    int count;

    char *result = readFile(fileName, &keys, &values, &count);

    if (result != NULL) {
        qsort(keys, count, sizeof(char *), compare);

        for (int i = 0; i < count; i++) {
            printf("%s = %s\n", keys[i], values[i]);
            free(keys[i]);
            free(values[i]);
        }

        free(keys);
        free(values);
    }

    return 0;
}