
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 1024
#define MAX_ARRAY_SIZE 1000

typedef enum {
    TYPE_STRING = 'S',
    TYPE_INT = 'I',
    TYPE_ARRAY = 'A'
} DataType;

typedef struct {
    char* data;
    size_t pos;
    size_t length;
} Buffer;

void initBuffer(Buffer* buffer, const char* data) {
    if (data == NULL) {
        buffer->data = NULL;
        buffer->length = 0;
        buffer->pos = 0;
        return;
    }
    
    buffer->length = strlen(data);
    buffer->data = (char*)malloc(buffer->length + 1);
    if (buffer->data != NULL) {
        strcpy(buffer->data, data);
        buffer->pos = 0;
    }
}

void freeBuffer(Buffer* buffer) {
    if (buffer->data != NULL) {
        free(buffer->data);
        buffer->data = NULL;
    }
    buffer->length = 0;
    buffer->pos = 0;
}

bool readChar(Buffer* buffer, char* c) {
    if (buffer->pos >= buffer->length) {
        return false;
    }
    *c = buffer->data[buffer->pos++];
    return true;
}

bool readInt(Buffer* buffer, int* value) {
    char* endptr;
    if (buffer->pos >= buffer->length) {
        return false;
    }
    
    *value = (int)strtol(buffer->data + buffer->pos, &endptr, 10);
    if (endptr == buffer->data + buffer->pos) {
        return false;
    }
    
    buffer->pos = endptr - buffer->data;
    return true;
}

bool readString(Buffer* buffer, char* str, size_t maxLen) {
    size_t i = 0;
    char c;
    
    // Skip whitespace
    while (buffer->pos < buffer->length && 
           (buffer->data[buffer->pos] == ' ' || buffer->data[buffer->pos] == '\\t')) {
        buffer->pos++;
    }
    
    while (buffer->pos < buffer->length && 
           buffer->data[buffer->pos] != ' ' && 
           buffer->data[buffer->pos] != '\\t' && 
           i < maxLen - 1) {
        str[i++] = buffer->data[buffer->pos++];
    }
    
    str[i] = '\\0';
    return i > 0;
}

void deserializeData(const char* data) {
    if (data == NULL) {
        printf("Error: Input data is NULL\\n");
        return;
    }
    
    Buffer buffer;
    initBuffer(&buffer, data);
    
    if (buffer.data == NULL) {
        printf("Error: Failed to initialize buffer\\n");
        return;
    }
    
    char type;
    if (!readChar(&buffer, &type)) {
        printf("Error: Failed to read type\\n");
        freeBuffer(&buffer);
        return;
    }
    
    switch (type) {
        case TYPE_STRING: {
            char str[MAX_STRING_LENGTH];
            if (readString(&buffer, str, MAX_STRING_LENGTH)) {
                printf("Deserialized string: %s\\n", str);
            } else {
                printf("Error: Failed to read string\\n");
            }
            break;
        }
        
        case TYPE_INT: {
            int value;
            if (readInt(&buffer, &value)) {
                printf("Deserialized int: %d\\n", value);
            } else {
                printf("Error: Failed to read integer\\n");
            }
            break;
        }
        
        case TYPE_ARRAY: {
            int size;
            if (!readInt(&buffer, &size) || size < 0 || size > MAX_ARRAY_SIZE) {
                printf("Error: Invalid array size\\n");
                break;
            }
            
            printf("Deserialized array of size %d:\\n", size);
            for (int i = 0; i < size; i++) {
                char str[MAX_STRING_LENGTH];
                if (readString(&buffer, str, MAX_STRING_LENGTH)) {
                    printf("  Item %d: %s\\n", i, str);
                } else {
                    printf("Error: Failed to read array item %d\\n", i);
                    break;
                }
            }
            break;
        }
        
        default:
            printf("Error: Unknown type '%c'\\n", type);
    }
    
    freeBuffer(&buffer);
}

int main() {
    // Test 1: Valid string
    printf("Test 1:\\n");
    deserializeData("S Hello");
    
    // Test 2: Valid integer
    printf("\\nTest 2:\\n");
    deserializeData("I 42");
    
    // Test 3: Valid array
    printf("\\nTest 3:\\n");
    deserializeData("A 2 test1 test2");
    
    // Test 4: NULL input
    printf("\\nTest 4:\\n");
    deserializeData(NULL);
    
    // Test 5: Invalid type
    printf("\\nTest 5:\\n");
    deserializeData("X invalid");
    
    return 0;
}
