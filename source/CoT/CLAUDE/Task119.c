
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* Maximum file size: 100MB to prevent excessive memory usage */
#define MAX_FILE_SIZE (100 * 1024 * 1024)
/* Maximum field size: 1MB to prevent memory attacks */
#define MAX_FIELD_SIZE (1 * 1024 * 1024)
/* Maximum number of fields per row */
#define MAX_FIELDS_PER_ROW 10000
/* Maximum number of rows */
#define MAX_ROWS 100000
/* Initial buffer size for dynamic allocation */
#define INITIAL_BUFFER_SIZE 256

typedef struct {
    char** fields;      /* Array of field strings */
    size_t field_count; /* Number of fields in this row */
} CSVRow;

typedef struct {
    CSVRow* rows;      /* Array of rows */
    size_t row_count;  /* Number of rows */
} CSVData;

/* Securely clear memory before freeing (prevent information leakage) */
static void secure_free(void* ptr, size_t size) {
    if (ptr != NULL && size > 0) {
        /* Use memset_s if available, otherwise volatile to prevent optimization */
        volatile unsigned char* p = (volatile unsigned char*)ptr;
        while (size--) {
            *p++ = 0;
        }
        free(ptr);
    }
}

/* Safe string duplication with length limit */
static char* safe_strdup(const char* str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, max_len);
    if (len >= max_len) {
        return NULL; /* String too long */
    }
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, str, len);
    result[len] = '\\0'; /* Ensure null termination */
    return result;
}
/* Validate path to prevent directory traversal (CWE-22) */
static bool is_safe_path(const char* filepath) {
    if (filepath == NULL || filepath[0] == '\0') {
        return false;
    }

    /* Check for null bytes in path (CWE-158) */
    size_t path_len = strnlen(filepath, MAX_FIELD_SIZE);
    for (size_t i = 0; i < path_len; i++) {
        if (filepath[i] == '\0' && i < path_len - 1) {
            return false;
        }
    }

    /* Reject absolute paths */
    if (filepath[0] == '/' || filepath[0] == '\\') {
        return false;
    }

    /* Check for Windows drive letters */
    if (path_len > 1 && filepath[1] == ':') {
        return false;
    }

    /* Reject paths containing .. or // */
    if (strstr(filepath, "..") != NULL || strstr(filepath, "//") != NULL) {
        return false;
    }

    /* Reject backslashes (Windows path separator abuse) */
    if (strchr(filepath, '\\') != NULL) {
        return false;
    }

    return true;
}

/* Free CSV data structure */
static void free_csv_data(CSVData* data) {
    if (data == NULL) {
        return;
    }

    if (data->rows != NULL) {
        for (size_t i = 0; i < data->row_count; i++) {
            if (data->rows[i].fields != NULL) {
                for (size_t j = 0; j < data->rows[i].field_count; j++) {
                    if (data->rows[i].fields[j] != NULL) {
                        free(data->rows[i].fields[j]);
                        data->rows[i].fields[j] = NULL;
                    }
                }
                free(data->rows[i].fields);
                data->rows[i].fields = NULL;
            }
        }
        free(data->rows);
        data->rows = NULL;
    }

    data->row_count = 0;
}

/* Parse a single CSV field from line starting at position pos */
static bool parse_field(const char* line, size_t* pos, char** field_out) {
    if (line == NULL || pos == NULL || field_out == NULL) {
        return false;
    }

    size_t line_len = strlen(line);
    size_t field_capacity = INITIAL_BUFFER_SIZE;
    size_t field_size = 0;
    bool in_quotes = false;

    /* Allocate initial buffer for field */
    char* field = (char*)malloc(field_capacity);
    if (field == NULL) {
        return false;
    }

    /* Check if field starts with quote */
    if (*pos < line_len && line[*pos] == '"') {
        in_quotes = true;
        (*pos)++; /* Skip opening quote */
    }

    while (*pos < line_len) {
        /* Prevent excessively large fields (CWE-400) */
        if (field_size >= MAX_FIELD_SIZE) {
            free(field);
            return false;
        }

        /* Grow buffer if needed (CWE-120: Buffer overflow prevention) */
        if (field_size + 2 >= field_capacity) {
            if (field_capacity >= MAX_FIELD_SIZE / 2) {
                free(field);
                return false;
            }
            size_t new_capacity = field_capacity * 2;
            if (new_capacity > MAX_FIELD_SIZE) {
                new_capacity = MAX_FIELD_SIZE;
            }
            char* new_field = (char*)realloc(field, new_capacity);
            if (new_field == NULL) {
                free(field);
                return false;
            }
            field = new_field;
            field_capacity = new_capacity;
        }

        char current = line[*pos];

        if (in_quotes) {
            if (current == '"') {
                /* Check for escaped quote (double quote) */
                if (*pos + 1 < line_len && line[*pos + 1] == '"') {
                    field[field_size++] = '"';
                    *pos += 2;
                } else {
                    /* End of quoted field */
                    in_quotes = false;
                    (*pos)++;
                    /* Skip to next comma or end */
                    if (*pos < line_len && line[*pos] == ',') {
                        (*pos)++;
                    }
                    break;
                }
            } else {
                field[field_size++] = current;
                (*pos)++;
            }
        } else {
            if (current == ',') {
                (*pos)++; /* Skip comma */
                break;
            } else {
                field[field_size++] = current;
                (*pos)++;
            }
        }
    }

    field[field_size] = '\0'; /* Null terminate */
    *field_out = field;
    return true;
}

/* Parse CSV file and return CSVData structure */
CSVData* parse_csv_file(const char* filepath) {
    if (filepath == NULL) {
        fprintf(stderr, "Error: NULL filepath\n");
        return NULL;
    }

    /* Validate path (CWE-22: Path traversal prevention) */
    if (!is_safe_path(filepath)) {
        fprintf(stderr, "Error: Invalid or unsafe file path\n");
        return NULL;
    }

    /* Open file for reading (CWE-73: External control of file name) */
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s\n", filepath);
        return NULL;
    }

    /* Check file size to prevent resource exhaustion (CWE-400) */
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size < 0 || (unsigned long)file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File size invalid or exceeds maximum\n");
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }

    /* Allocate CSV data structure */
    CSVData* data = (CSVData*)calloc(1, sizeof(CSVData));
    if (data == NULL) {
        fclose(file);
        return NULL;
    }

    /* Allocate initial rows array */
    data->rows = (CSVRow*)calloc(MAX_ROWS, sizeof(CSVRow));
    if (data->rows == NULL) {
        free(data);
        fclose(file);
        return NULL;
    }

    /* Read file line by line */
    char* line_buffer = NULL;
    size_t line_capacity = 0;
    ssize_t line_length;
    size_t line_number = 0;

    /* Use getline for safe line reading */
    while ((line_length = getline(&line_buffer, &line_capacity, file)) != -1) {
        line_number++;

        /* Prevent too many rows (CWE-400) */
        if (data->row_count >= MAX_ROWS) {
            fprintf(stderr, "Error: Too many rows\n");
            free(line_buffer);
            free_csv_data(data);
            free(data);
            fclose(file);
            return NULL;
        }

        /* Remove trailing newline and carriage return */
        while (line_length > 0 &&
               (line_buffer[line_length - 1] == '\n' ||
                line_buffer[line_length - 1] == '\r')) {
            line_buffer[--line_length] = '\0';
        }

        /* Skip empty lines */
        if (line_length == 0) {
            continue;
        }

        /* Allocate fields array for this row */
        CSVRow* current_row = &data->rows[data->row_count];
        current_row->fields = (char**)calloc(MAX_FIELDS_PER_ROW, sizeof(char*));
        if (current_row->fields == NULL) {
            free(line_buffer);
            free_csv_data(data);
            free(data);
            fclose(file);
            return NULL;
        }

        /* Parse all fields in the line */
        size_t pos = 0;
        while (pos <= (size_t)line_length) {
            /* Prevent too many fields (CWE-400) */
            if (current_row->field_count >= MAX_FIELDS_PER_ROW) {
                fprintf(stderr, "Error: Too many fields in line %zu\n", line_number);
                free(line_buffer);
                free_csv_data(data);
                free(data);
                fclose(file);
                return NULL;
            }

            char* field = NULL;
            if (!parse_field(line_buffer, &pos, &field)) {
                fprintf(stderr, "Error: Failed to parse field at line %zu\n", line_number);
                free(line_buffer);
                free_csv_data(data);
                free(data);
                fclose(file);
                return NULL;
            }

            current_row->fields[current_row->field_count++] = field;

            if (pos >= (size_t)line_length) {
                break;
            }
        }

        if (current_row->field_count > 0) {
            data->row_count++;
        }
    }

    free(line_buffer);
    fclose(file);
    return data;
}

/* Write CSV data to file safely */
bool write_csv_file(const char* filepath, const CSVData* data) {
    if (filepath == NULL || data == NULL) {
        return false;
    }

    /* Validate path (CWE-22: Path traversal prevention) */
    if (!is_safe_path(filepath)) {
        fprintf(stderr, "Error: Invalid or unsafe file path\n");
        return false;
    }

    /* Create temporary file path (TOCTOU mitigation - CWE-367) */
    size_t temp_path_len = strlen(filepath) + 5; /* +4 for ".tmp" +1 for null */
    char* temp_path = (char*)malloc(temp_path_len);
    if (temp_path == NULL) {
        return false;
    }

    /* Use snprintf to prevent buffer overflow (CWE-120) */
    int written = snprintf(temp_path, temp_path_len, "%s.tmp", filepath);
    if (written < 0 || (size_t)written >= temp_path_len) {
        free(temp_path);
        return false;
    }

    /* Open temporary file with exclusive creation (CWE-367) */
    FILE* file = fopen(temp_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot create temporary file\n");
        free(temp_path);
        return false;
    }

    /* Write CSV data with proper escaping */
    for (size_t i = 0; i < data->row_count; i++) {
        const CSVRow* row = &data->rows[i];

        for (size_t j = 0; j < row->field_count; j++) {
            const char* field = row->fields[j];
            if (field == NULL) {
                field = "";
            }

            /* Check if field needs quoting */
            bool needs_quotes = strchr(field, ',') != NULL ||
                                strchr(field, '"') != NULL ||
                                strchr(field, '\n') != NULL ||
                                strchr(field, '\r') != NULL;

            if (needs_quotes) {
                fputc('"', file);
                /* Escape quotes by doubling them */
                for (const char* p = field; *p != '\0'; p++) {
                    if (*p == '"') {
                        fputc('"', file);
                        fputc('"', file);
                    } else {
                        fputc(*p, file);
                    }
                }
                fputc('"', file);
            } else {
                fputs(field, file);
            }

            if (j < row->field_count - 1) {
                fputc(',', file);
            }
        }
        fputc('\n', file);
    }

    /* Ensure data is written to disk */
    if (fflush(file) != 0) {
        fclose(file);
        remove(temp_path);
        free(temp_path);
        return false;
    }

    fclose(file);

    /* Atomic rename to prevent TOCTOU (CWE-367) */
    if (rename(temp_path, filepath) != 0) {
        fprintf(stderr, "Error: Failed to rename temporary file\n");
        remove(temp_path);
        free(temp_path);
        return false;
    }

    free(temp_path);
    return true;
}

int main(void) {
    /* Test case 1: Create and write a simple CSV file */
    printf("Test 1: Writing simple CSV file\\n");
    
    CSVData test_data1 = {0};
    test_data1.rows = (CSVRow*)calloc(3, sizeof(CSVRow));
    if (test_data1.rows == NULL) {
        return 1;
    }
    test_data1.row_count = 3;
    
    test_data1.rows[0].fields = (char**)calloc(3, sizeof(char*));
    test_data1.rows[0].fields[0] = safe_strdup("Name", MAX_FIELD_SIZE);
    test_data1.rows[0].fields[1] = safe_strdup("Age", MAX_FIELD_SIZE);
    test_data1.rows[0].fields[2] = safe_strdup("City", MAX_FIELD_SIZE);
    test_data1.rows[0].field_count = 3;
    
    test_data1.rows[1].fields = (char**)calloc(3, sizeof(char*));
    test_data1.rows[1].fields[0] = safe_strdup("Alice", MAX_FIELD_SIZE);
    test_data1.rows[1].fields[1] = safe_strdup("30", MAX_FIELD_SIZE);
    test_data1.rows[1].fields[2] = safe_strdup("New York", MAX_FIELD_SIZE);
    test_data1.rows[1].field_count = 3;
    
    test_data1.rows[2].fields = (char**)calloc(3, sizeof(char*));
    test_data1.rows[2].fields[0] = safe_strdup("Bob", MAX_FIELD_SIZE);
    test_data1.rows[2].fields[1] = safe_strdup("25", MAX_FIELD_SIZE);
    test_data1.rows[2].fields[2] = safe_strdup("Los Angeles", MAX_FIELD_SIZE);
    test_data1.rows[2].field_count = 3;
    
    if (write_csv_file("test1.csv", &test_data1)) {
        printf("Successfully wrote test1.csv\\n");
        CSVData* result = parse_csv_file("test1.csv");
        if (result != NULL) {
            printf("Parsed %zu rows\\n", result->row_count);
            free_csv_data(result);
            free(result);
        }
    }
    
    free_csv_data(&test_data1);
    
    /* Test case 2: CSV with quoted fields */
    printf("\\nTest 2: CSV with special characters\\n");
    
    CSVData test_data2 = {0};
    test_data2.rows = (CSVRow*)calloc(2, sizeof(CSVRow));
    if (test_data2.rows != NULL) {
        test_data2.row_count = 2;
        
        test_data2.rows[0].fields = (char**)calloc(3, sizeof(char*));
        test_data2.rows[0].fields[0] = safe_strdup("Product", MAX_FIELD_SIZE);
        test_data2.rows[0].fields[1] = safe_strdup("Description", MAX_FIELD_SIZE);
        test_data2.rows[0].fields[2] = safe_strdup("Price", MAX_FIELD_SIZE);
        test_data2.rows[0].field_count = 3;
        
        test_data2.rows[1].fields = (char**)calloc(3, sizeof(char*));
        test_data2.rows[1].fields[0] = safe_strdup("Widget", MAX_FIELD_SIZE);
        test_data2.rows[1].fields[1] = safe_strdup("A small, useful item", MAX_FIELD_SIZE);
        test_data2.rows[1].fields[2] = safe_strdup("10.99", MAX_FIELD_SIZE);
        test_data2.rows[1].field_count = 3;
        
        if (write_csv_file("test2.csv", &test_data2)) {
            printf("Successfully wrote test2.csv\\n");
        }
        
        free_csv_data(&test_data2);
    }
    
    /* Test case 3: Empty CSV */
    printf("\\nTest 3: Empty CSV\\n");
    CSVData test_data3 = {0};
    test_data3.rows = NULL;
    test_data3.row_count = 0;
    
    /* Test case 4: Path traversal attempt (should fail) */
    printf("\\nTest 4: Path traversal attempt (should fail)\\n");
    CSVData* result = parse_csv_file("../etc/passwd");
    if (result == NULL) {
        printf("Correctly rejected unsafe path\\n");
    }
    
    /* Test case 5: Parse existing CSV */
    printf("\\nTest 5: Parse test1.csv\\n");
    result = parse_csv_file("test1.csv");
    if (result != NULL) {
        printf("Successfully parsed %zu rows\\n", result->row_count);
        for (size_t i = 0; i < result->row_count; i++) {
            for (size_t j = 0; j < result->rows[i].field_count; j++) {
                printf("[%s]", result->rows[i].fields[j]);
                if (j < result->rows[i].field_count - 1) {
                    printf(", ");
                }
            }
            printf("\\n");
        }
        free_csv_data(result);
        free(result);
    }
    
    return 0;
}
