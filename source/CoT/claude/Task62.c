
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

const char* find_json_root(const char* json_str) {
    if (json_str == NULL || strlen(json_str) == 0) {
        return "";
    }
    
    // Find first non-whitespace character
    while (*json_str && isspace(*json_str)) {
        json_str++;
    }
    
    if (*json_str == '\0') {
        return "";
    }
    
    char first_char = *json_str;
    
    if (first_char == '{') {
        return "object";
    } else if (first_char == '[') {
        return "array";
    } else if (first_char == '"') {
        return "string";
    } else if (isdigit(first_char) || first_char == '-') {
        return "number";
    } else if (strncmp(json_str, "true", 4) == 0 || strncmp(json_str, "false", 5) == 0) {
        return "boolean";
    } else if (strncmp(json_str, "null", 4) == 0) {
        return "null";
    }
    
    return "invalid";
}
//
// int main() {
//     // Test cases
//     const char* tests[] = {
//         "{\\"name\\": \\"John\\", \\"age\\": 30}",
//         "[1, 2, 3, 4]",
//         "\\"Hello World\\"",
//         "42",
//         "true"
//     };
//
//     int num_tests = sizeof(tests) / sizeof(tests[0]);
//
//     for (int i = 0; i < num_tests; i++) {
//         printf("Test %d: %s\\n", i + 1, find_json_root(tests[i]));
//     }
//
//     return 0;
// }
