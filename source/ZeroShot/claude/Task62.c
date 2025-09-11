
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL
} JsonType;

typedef struct JsonElement {
    JsonType type;
    union {
        struct {
            char** keys;
            struct JsonElement** values;
            int size;
        } object;
        struct {
            struct JsonElement** elements;
            int size;
        } array;
        char* string;
        double number;
        int boolean;
    } value;
} JsonElement;

char* trim(const char* str) {
    while (isspace(*str)) str++;
    if (*str == 0) return strdup("");
    
    const char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    int len = end - str + 1;
    char* result = (char*)malloc(len + 1);
    strncpy(result, str, len);
    result[len] = '\\0';
    return result;
}

JsonElement* parseJson(const char* json) {
    char* trimmed = trim(json);
    if (strlen(trimmed) == 0) {
        free(trimmed);
        return NULL;
    }

    JsonElement* element = (JsonElement*)malloc(sizeof(JsonElement));

    // Object
    if (trimmed[0] == '{') {
        element->type = JSON_OBJECT;
        element->value.object.size = 0;
        element->value.object.keys = NULL;
        element->value.object.values = NULL;
        // Basic object parsing implementation
        free(trimmed);
        return element;
    }

    // Array
    if (trimmed[0] == '[') {
        element->type = JSON_ARRAY;
        element->value.array.size = 0;
        element->value.array.elements = NULL;
        // Basic array parsing implementation
        free(trimmed);
        return element;
    }

    // String
    if (trimmed[0] == '"') {
        element->type = JSON_STRING;
        int len = strlen(trimmed) - 2;
        element->value.string = (char*)malloc(len + 1);
        strncpy(element->value.string, trimmed + 1, len);
        element->value.string[len] = '\\0';
        free(trimmed);
        return element;
    }

    // Boolean
    if (strcmp(trimmed, "true") == 0) {
        element->type = JSON_BOOLEAN;
        element->value.boolean = 1;
        free(trimmed);
        return element;
    }
    if (', type='text')