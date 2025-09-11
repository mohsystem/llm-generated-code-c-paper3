#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

char* get_root_element(const char* json_string) {
    if (json_string == NULL || strlen(json_string) == 0) {
        fprintf(stderr, "Input string is null or empty\n");
        exit(EXIT_FAILURE);
    }
    struct json_object* json_obj = json_tokener_parse(json_string);
    if (json_obj == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        exit(EXIT_FAILURE);
    }
    struct json_object_iter iter;
    json_object_object_foreachC(json_obj, iter) {
        const char* key = iter.key;
        json_object_put(json_obj); // Free memory
        return strdup(key);
    }
    json_object_put(json_obj); // Free memory
    return NULL;
}

int main() {
    // Test cases
    printf("%s\n", get_root_element("{\"root\": {\"key\": \"value\"}}")); // Output: root
    printf("%s\n", get_root_element("{\"anotherRoot\": {\"key\": \"value\"}}")); // Output: anotherRoot
    printf("%s\n", get_root_element("{\"nested\": {\"inside\": {\"key\": \"value\"}}}")); // Output: nested
    printf("%s\n", get_root_element("{\"empty\": {}}")); // Output: empty
    printf("%s\n", get_root_element("{\"onlyKey\": \"onlyValue\"}")); // Output: onlyKey
    return 0;
}