#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

/* Maximum file size to prevent excessive memory usage (10MB) */
#define MAX_FILE_SIZE (10 * 1024 * 1024)
/* Maximum number of records to prevent DoS */
#define MAX_RECORDS 100000
/* Maximum key/value length */
#define MAX_KV_LENGTH 1024
/* Maximum line length */
#define MAX_LINE_LENGTH (MAX_KV_LENGTH * 2 + 2)
/* Maximum path length */
#define MAX_PATH_LENGTH 4096

typedef struct {
    char key[MAX_KV_LENGTH + 1];   /* +1 for null terminator */
    char value[MAX_KV_LENGTH + 1]; /* +1 for null terminator */
} KeyValue;

/* Securely clear sensitive data from memory */
void secureClear(void* ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (len--) {
        *p++ = 0;
    }
}

/* Validates that path doesn't contain directory traversal attempts */
bool validatePath(const char* path) {
    if (path == NULL) return false;

    size_t len = strnlen(path, MAX_PATH_LENGTH + 1);
    if (len == 0 || len > MAX_PATH_LENGTH) {
        return false;
    }

    /* Reject paths with directory traversal patterns */
    if (strstr(path, "..") != NULL) {
        return false;
    }

    /* Reject absolute paths */
    if (path[0] == '/' || path[0] == '\\') {
        return false;
    }

    return true;
}

/* Trim whitespace from string in place */
void trimWhitespace(char* str) {
    if (str == NULL) return;

    /* Trim leading whitespace */
    char* start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    /* If string is all whitespace */
    if (*start == '\0') {
        str[0] = '\0';
        return;
    }

    /* Trim trailing whitespace */
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';

    /* Move trimmed string to beginning */
    if (start != str) {
        size_t len = strlen(start);
        memmove(str, start, len + 1); /* +1 for null terminator */
    }
}

/* Safely parse a line into key-value pair */
bool parseLine(const char* line, KeyValue* kv) {
    if (line == NULL || kv == NULL) return false;

    /* Initialize output structure */
    memset(kv, 0, sizeof(KeyValue));

    size_t lineLen = strnlen(line, MAX_LINE_LENGTH);
    if (lineLen == 0 || lineLen >= MAX_LINE_LENGTH) {
        return false;
    }

    /* Find delimiter */
    const char* delim = strchr(line, '=');
    if (delim == NULL) {
        delim = strchr(line, ':');
        if (delim == NULL) {
            return false;
        }
    }

    /* Calculate key and value lengths with bounds checking */
    size_t keyLen = (size_t)(delim - line);
    size_t valueLen = lineLen - keyLen - 1;

    if (keyLen == 0 || keyLen > MAX_KV_LENGTH ||
        valueLen == 0 || valueLen > MAX_KV_LENGTH) {
        return false;
    }

    /* Copy key with bounds checking */
    if (keyLen >= sizeof(kv->key)) {
        return false;
    }
    memcpy(kv->key, line, keyLen);
    kv->key[keyLen] = '\0'; /* Ensure null termination */

    /* Copy value with bounds checking */
    if (valueLen >= sizeof(kv->value)) {
        return false;
    }
    memcpy(kv->value, delim + 1, valueLen);
    kv->value[valueLen] = '\0'; /* Ensure null termination */

    /* Trim whitespace */
    trimWhitespace(kv->key);
    trimWhitespace(kv->value);

    /* Validate after trimming */
    if (kv->key[0] == '\0' || kv->value[0] == '\0') {
        return false;
    }

    return true;
}

/* Comparison function for qsort */
int compareKeyValue(const void* a, const void* b) {
    const KeyValue* kv1 = (const KeyValue*)a;
    const KeyValue* kv2 = (const KeyValue*)b;
    return strcmp(kv1->key, kv2->key);
}

/* Read and sort key-value records from file */
KeyValue* readAndSortRecords(const char* filename, size_t* outCount) {
    if (filename == NULL || outCount == NULL) {
        return NULL;
    }

    *outCount = 0;

    /* Validate file path */
    if (!validatePath(filename)) {
        fprintf(stderr, "Error: Invalid file path\n");
        return NULL;
    }

    /* Open file for reading - use "r" mode with careful validation */
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s\n", filename);
        return NULL;
    }

    /* Check file size to prevent excessive memory usage */
    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error: Cannot seek file\n");
        fclose(file);
        return NULL;
    }

    long fileSize = ftell(file);
    if (fileSize < 0 || (unsigned long)fileSize > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File too large or invalid\n");
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Error: Cannot seek to beginning\n");
        fclose(file);
        return NULL;
    }

    /* Allocate initial buffer for records */
    size_t capacity = 100;
    KeyValue* records = (KeyValue*)calloc(capacity, sizeof(KeyValue));
    if (records == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    size_t count = 0;

    /* Read file line by line with bounds checking */
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_RECORDS) {
        /* Remove newline if present */
        size_t len = strnlen(line, sizeof(line));
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }

        /* Grow buffer if needed with overflow check */
        if (count >= capacity) {
            if (capacity > SIZE_MAX / 2 / sizeof(KeyValue)) {
                fprintf(stderr, "Error: Capacity overflow\n");
                break;
            }
            size_t newCapacity = capacity * 2;
            if (newCapacity > MAX_RECORDS) {
                newCapacity = MAX_RECORDS;
            }

            KeyValue* newRecords = (KeyValue*)realloc(records, newCapacity * sizeof(KeyValue));
            if (newRecords == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                break;
            }
            records = newRecords;
            /* Initialize new memory */
            memset(records + capacity, 0, (newCapacity - capacity) * sizeof(KeyValue));
            capacity = newCapacity;
        }

        /* Parse and store record */
        if (parseLine(line, &records[count])) {
            count++;
        }
    }

    fclose(file);

    if (count >= MAX_RECORDS) {
        fprintf(stderr, "Warning: Maximum record count reached\n");
    }

    /* Sort records by key */
    if (count > 0) {
        qsort(records, count, sizeof(KeyValue), compareKeyValue);
    }

    *outCount = count;
    return records;
}

int main(void) {
    /* Test case 1: Basic key-value pairs */
    {
        FILE* out = fopen("test1.txt", "w");
        if (out != NULL) {
            fprintf(out, "name=John\n");
            fprintf(out, "age=30\n");
            fprintf(out, "city=NYC\n");
            fclose(out);
        }

        size_t count = 0;
        KeyValue* result = readAndSortRecords("test1.txt", &count);
        printf("Test 1 - Basic sorting:\n");
        if (result != NULL) {
            for (size_t i = 0; i < count; i++) {
                printf("%s=%s\n", result[i].key, result[i].value);
            }
            secureClear(result, count * sizeof(KeyValue));
            free(result);
        }
        printf("\n");
    }

    /* Test case 2: Colon delimiter */
    {
        FILE* out = fopen("test2.txt", "w");
        if (out != NULL) {
            fprintf(out, "zebra:animal\n");
            fprintf(out, "apple:fruit\n");
            fprintf(out, "carrot:vegetable\n");
            fclose(out);
        }

        size_t count = 0;
        KeyValue* result = readAndSortRecords("test2.txt", &count);
        printf("Test 2 - Colon delimiter:\n");
        if (result != NULL) {
            for (size_t i = 0; i < count; i++) {
                printf("%s:%s\n", result[i].key, result[i].value);
            }
            secureClear(result, count * sizeof(KeyValue));
            free(result);
        }
        printf("\n");
    }

    /* Test case 3: Whitespace handling */
    {
        FILE* out = fopen("test3.txt", "w");
        if (out != NULL) {
            fprintf(out, "  key1  =  value1  \n");
            fprintf(out, "key2=value2\n");
            fprintf(out, "\n");
            fprintf(out, "key0=value0\n");
            fclose(out);
        }

        size_t count = 0;
        KeyValue* result = readAndSortRecords("test3.txt", &count);
        printf("Test 3 - Whitespace handling:\n");
        if (result != NULL) {
            for (size_t i = 0; i < count; i++) {
                printf("%s=%s\n", result[i].key, result[i].value);
            }
            secureClear(result, count * sizeof(KeyValue));
            free(result);
        }
        printf("\n");
    }

    /* Test case 4: Invalid file path */
    {
        printf("Test 4 - Invalid path (../etc/passwd):\n");
        size_t count = 0;
        KeyValue* result = readAndSortRecords("../etc/passwd", &count);
        printf("Records read: %zu\n\n", count);
        if (result != NULL) {
            secureClear(result, count * sizeof(KeyValue));
            free(result);
        }
    }

    /* Test case 5: Empty file */
    {
        FILE* out = fopen("test5.txt", "w");
        if (out != NULL) {
            fclose(out);
        }

        size_t count = 0;
        KeyValue* result = readAndSortRecords("test5.txt", &count);
        printf("Test 5 - Empty file:\n");
        printf("Records read: %zu\n", count);
        if (result != NULL) {
            secureClear(result, count * sizeof(KeyValue));
            free(result);
        }
    }

    return 0;
}
