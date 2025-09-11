#include <stdio.h>
#include <string.h>
#include <cJSON.h> // Make sure you have the cJSON library

// Note: This C implementation uses cJSON and requires manual memory management.

char* getRootElement(const char* jsonString) {
    cJSON* json = cJSON_Parse(jsonString);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return NULL;
    }

    if (cJSON_IsObject(json) && cJSON_GetArraySize(json) > 0) {
        char* rootName = strdup(cJSON_GetArrayItem(json, 0)->string);
        cJSON_Delete(json);  // Free the cJSON object
        return rootName;
    }
     cJSON_Delete(json); // Free the cJSON object

    return NULL;
}


int main() {
    char* test1 = "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}";
    char* test2 = "[{\"name\":\"John\", \"age\":30},{\"name\":\"Jane\", \"age\":25}]";
    char* test3 = "[]";
    char* test4 = "{}";
    char* test5 = "\"Just a string\"";


    printf("%s\n", getRootElement(test1)); // Output: name
    printf("%s\n", getRootElement(test2)); // Output: 
    printf("%s\n", getRootElement(test3)); // Output: 
    printf("%s\n", getRootElement(test4)); // Output:
    printf("%s\n", getRootElement(test5)); // Output: 

    return 0;
}