#include <stdio.h>
#include <string.h>
#include <jansson.h>

const char* getRootElement(const char* jsonString) {
    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);
    if (!root) {
        return NULL;
    }
    const char* key;
    void* iter = json_object_iter(root);
    if (iter) {
        key = json_object_iter_key(iter);
    } else {
        key = NULL;
    }
    json_decref(root);
    return key;
}

int main() {
    printf("%s\n", getRootElement("{\"name\": \"John\", \"age\": 30}"));
    printf("%s\n", getRootElement("{\"city\": \"New York\", \"country\": \"USA\"}"));
    printf("%s\n", getRootElement("{\"fruit\": \"Apple\", \"color\": \"Red\"}"));
    printf("%s\n", getRootElement("{\"car\": \"Toyota\", \"year\": 2020}"));
    printf("%s\n", getRootElement("{\"language\": \"Java\", \"version\": 11}"));
    return 0;
}