
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Security: Maximum payload size to prevent DoS attacks */
#define MAX_PAYLOAD_SIZE 10240
#define MAX_NAME_SIZE 1024

/* Security: Safe string operations with bounds checking */
typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} SafeString;

/* Security: Initialize SafeString with size validation */
SafeString* safestring_create(size_t initial_capacity) {
    if (initial_capacity == 0 || initial_capacity > MAX_PAYLOAD_SIZE) {
        return NULL;
    }
    
    SafeString* str = (SafeString*)malloc(sizeof(SafeString));
    if (str == NULL) {
        return NULL;
    }
    
    str->data = (char*)calloc(initial_capacity + 1, sizeof(char));
    if (str->data == NULL) {
        free(str);
        return NULL;
    }
    
    str->length = 0;
    str->capacity = initial_capacity;
    return str;
}

/* Security: Safe cleanup of SafeString */
void safestring_destroy(SafeString* str) {
    if (str != NULL) {
        if (str->data != NULL) {
            /* Security: Clear memory before free to prevent data leakage */
            memset(str->data, 0, str->capacity + 1);
            free(str->data);
        }
        free(str);
    }
}

/* Security: Safe character append with bounds checking */
int safestring_append_char(SafeString* str, char c) {
    if (str == NULL || str->data == NULL) {
        return 0;
    }
    
    /* Security: Check bounds before writing */
    if (str->length >= str->capacity) {
        return 0;
    }
    
    str->data[str->length++] = c;
    str->data[str->length] = '\0';
    return 1;
}
/* Security: Escape special JSON characters to prevent injection */
char* escape_json_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len > MAX_NAME_SIZE) {
        return NULL;
    }

    /* Security: Allocate buffer with size validation */
    SafeString* output = safestring_create(input_len * 2);
    if (output == NULL) {
        return NULL;
    }

    /* Security: Process each character safely with bounds checking */
    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];
        switch (c) {
            case '\\':
                if (!safestring_append_char(output, '\\') ||
                    !safestring_append_char(output, '\\')) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
            case '"':
                if (!safestring_append_char(output, '\\') ||
                    !safestring_append_char(output, '"')) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
            case '\n':
                if (!safestring_append_char(output, '\\') ||
                    !safestring_append_char(output, 'n')) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
            case '\r':
                if (!safestring_append_char(output, '\\') ||
                    !safestring_append_char(output, 'r')) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
            case '\t':
                if (!safestring_append_char(output, '\\') ||
                    !safestring_append_char(output, 't')) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
            default:
                if (!safestring_append_char(output, c)) {
                    safestring_destroy(output);
                    return NULL;
                }
                break;
        }
    }

    /* Security: Duplicate string safely before destroying SafeString */
    char* result = strdup(output->data);
    safestring_destroy(output);
    return result;
}

/* Security: Extract name from JSON payload with safe parsing */
char* extract_name_from_json(const char* payload) {
    if (payload == NULL) {
        return NULL;
    }

    /* Security: Find "name" key safely with bounds checking */
    const char* name_key = strstr(payload, "\"name\"");
    if (name_key == NULL) {
        return NULL;
    }

    /* Security: Find the colon after "name" */
    const char* colon = strchr(name_key, ':');
    if (colon == NULL) {
        return NULL;
    }

    /* Security: Skip whitespace and find opening quote */
    const char* ptr = colon + 1;
    while (*ptr && isspace((unsigned char) *ptr)) {
        ptr++;
    }

    if (*ptr != '"') {
        return NULL;
    }
    ptr++; /* Skip opening quote */

    /* Security: Extract value with length validation */
    const char* value_start = ptr;
    size_t value_len = 0;

    while (*ptr && *ptr != '"' && value_len < MAX_NAME_SIZE) {
        if (*ptr == '\\' && *(ptr + 1)) {
            ptr++; /* Skip escape character */
        }
        ptr++;
        value_len++;
    }

    if (*ptr != '"' || value_len == 0 || value_len >= MAX_NAME_SIZE) {
        return NULL;
    }

    /* Security: Allocate and copy with size validation */
    char* name = (char*) malloc(value_len + 1);
    if (name == NULL) {
        return NULL;
    }

    /* Security: Use safe string copy with explicit size */
    memcpy(name, value_start, value_len);
    name[value_len] = '\0';

    return name;
}

/* Security: Process payload with comprehensive input validation */
char* process_payload(const char* payload) {
    /* Security: Validate input is not NULL and within size limits */
    if (payload == NULL) {
        return strdup("{\"error\":\"Invalid input\"}");
    }

    size_t payload_len = strlen(payload);
    if (payload_len == 0) {
        return strdup("{\"error\":\"Invalid input\"}");
    }

    if (payload_len > MAX_PAYLOAD_SIZE) {
        return strdup("{\"error\":\"Payload too large\"}");
    }

    /* Security: Extract name safely with bounds checking */
    char* name = extract_name_from_json(payload);
    if (name == NULL) {
        return strdup("{\"error\":\"Missing name field\"}");
    }

    /* Security: Escape name for safe JSON output */
    char* escaped_name = escape_json_string(name);

    /* Security: Clear and free original name */
    memset(name, 0, strlen(name));
    free(name);

    if (escaped_name == NULL) {
        return strdup("{\"error\":\"Processing error\"}");
    }

    /* Security: Build result with size validation */
    size_t result_size = strlen(escaped_name) + 32;
    char* result = (char*) malloc(result_size);
    if (result == NULL) {
        memset(escaped_name, 0, strlen(escaped_name));
        free(escaped_name);
        return strdup("{\"error\":\"Memory error\"}");
    }

    /* Security: Use snprintf for safe string formatting */
    snprintf(result, result_size, "{\"name\":\"%s\"}", escaped_name);

    /* Security: Clear and free escaped name */
    memset(escaped_name, 0, strlen(escaped_name));
    free(escaped_name);

    return result;
}

int main(void) {
    printf("Web API simulation (C version)\\n");
    printf("Note: C doesn't have built-in HTTP server.\\n");
    printf("This demonstrates the payload processing logic.\\n\\n");
    
    /* Test cases */
    printf("Test cases:\\n");
    
    char* result1 = process_payload("{\"name\":\"John\"}");
    printf("1. Valid JSON: %s\\n", result1);
    free(result1);
    
    char* result2 = process_payload("{\"name\":\"O'Brien\"}");
    printf("2. Valid JSON with special chars: %s\\n", result2);
    free(result2);
    
    char* result3 = process_payload("{\"age\":30}");
    printf("3. Missing name field: %s\\n", result3);
    free(result3);
    
    char* result4 = process_payload("{invalid}");
    printf("4. Invalid JSON: %s\\n", result4);
    free(result4);
    
    char* result5 = process_payload(NULL);
    printf("5. NULL payload: %s\\n", result5);
    free(result5);
    
    return 0;
}
