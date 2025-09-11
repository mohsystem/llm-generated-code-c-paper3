#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h" // Assuming you have cJSON library

//  gcc task62.c cJSON.c -o task62

char* getRootElement(const char* jsonString) {
    cJSON* json = cJSON_Parse(jsonString);
    if (json == NULL) {
        return NULL;
    }

    if (cJSON_IsObject(json) && cJSON_GetArraySize(json) > 0) {

        char* rootElement = strdup(cJSON_GetObjectItem(json, cJSON_GetArrayItem(json->childKeys, 0)->valuestring)->string);
        cJSON_Delete(json); // Free allocated memory
        return rootElement;

    } else {
        cJSON_Delete(json); // Free memory even if parsing fails
        return NULL; 
    }
}


int main() {
    char* test1 = "{\"name\": \"John\", \"age\": 30}";
    char* test2 = "[{\"name\": \"John\"}, {\"name\": \"Jane\"}]";
    char* test3 = "123";
    char* test4 = "\"hello\"";
    char* test5 = "{}";

    printf("Test 1: %s\n", getRootElement(test1)); // Output: name
    printf("Test 2: %s\n", getRootElement(test2)); // Output: (null)
    printf("Test 3: %s\n", getRootElement(test3)); // Output: (null)
    printf("Test 4: %s\n", getRootElement(test4)); // Output: (null)
    printf("Test 5: %s\n", getRootElement(test5)); // Output: (null)

    return 0;
}