
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARRAY_SIZE 100
#define MAX_STRING_LENGTH 256

// Structure to hold deserialized data
typedef struct {
    char** strings;
    int count;
} StringArray;

// Function to trim whitespace
void trim(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;
    
    while(isspace((unsigned char)*start)) start++;
    while(end > start && isspace((unsigned char)*end)) end--;
    
    *(end + 1) = '\\0';
    memmove(str, start, end - start + 2);
}

// Main deserialization function
StringArray* deserialize(const char* input) {
    if (!input || input[0] != '{' || input[strlen(input)-1] != '}') {
        return NULL;
    }
    
    StringArray* result = (StringArray*)malloc(sizeof(StringArray));
    result->strings = (char**)malloc(MAX_ARRAY_SIZE * sizeof(char*));
    result->count = 0;
    
    // Remove braces and create working copy
    char* data = strdup(input + 1);
    data[strlen(data)-1] = '\\0';
    
    char* token = strtok(data, ",");
    while (token && result->count < MAX_ARRAY_SIZE) {
        trim(token);
        
        // Validate string format (must be in quotes)
        if (strlen(token) < 2 || token[0] != '"' || token[strlen(token)-1] != '"') {
            free(data);
            for (int i = 0; i < result->count; i++) {
                free(result->strings[i]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        
        // Remove quotes and copy string
        token[strlen(token)-1] = '\\0';
        result->strings[result->count] = strdup(token + 1);
        result->count++;
        
        token = strtok(NULL, ",");
    }
    
    free(data);
    return result;
}

// Function to free memory
void freeStringArray(StringArray* arr) {
    if (arr) {
        for (int i = 0; i < arr->count; i++) {
            free(arr->strings[i]);
        }
        free(arr->strings);
        free(arr);
    }
}

// Print function for testing
void printStringArray(StringArray* arr) {
    if (!arr) {
        printf("NULL array\\n");
        return;
    }
    printf("Array size: %d, Contents: ", arr->count);
    for (int i = 0; i < arr->count; i++) {
        printf("%s ", arr->strings[i]);
    }
    printf("\\n");
}

int main() {
    // Test case 1: Valid array with multiple strings
    const char* test1 = "{\\"hello\\",\\"world\\"}";
    StringArray* result1 = deserialize(test1);
    printf("Test 1: ");
    printStringArray(result1);
    freeStringArray(result1);

    // Test case 2: Single string
    const char* test2 = "{\\"test\\"}";
    StringArray* result2 = deserialize(test2);
    printf("Test 2: ");
    printStringArray(result2);
    freeStringArray(result2);

    // Test case 3: Empty array
    const char* test3 = "{}";
    StringArray* result3 = deserialize(test3);
    printf("Test 3: ");
    printStringArray(result3);
    freeStringArray(result3);

    // Test case 4: Invalid format (missing braces)
    const char* test4 = "\\"hello\\",\\"world\\"";
    StringArray* result4 = deserialize(test4);
    printf("Test 4: ");
    printStringArray(result4);
    freeStringArray(result4);

    // Test case 5: Invalid string format
    const char* test5 = "{hello,world}";
    StringArray* result5 = deserialize(test5);
    printf("Test 5: ");
    printStringArray(result5);
    freeStringArray(result5);

    return 0;
}
