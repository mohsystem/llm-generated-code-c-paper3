#include <stdio.h>
#include <jansson.h>

const char* getRootElement(const char* jsonString) {
    json_t* root = json_loads(jsonString, 0, NULL);
    json_t* key = json_object_iter_key(json_object_iter(root));
    return json_string_value(key);
}

int main() {
    printf("%s\n", getRootElement("{\"root\": {\"child1\": \"value1\", \"child2\": \"value2\"}}"));
    printf("%s\n", getRootElement("{\"anotherRoot\": {\"child\": \"value\"}}"));
    printf("%s\n", getRootElement("{\"rootElement\": {\"nested\": {\"deeply\": \"nestedValue\"}}}"));
    printf("%s\n", getRootElement("{\"singleRoot\": \"singleValue\"}"));
    printf("%s\n", getRootElement("{\"emptyRoot\": {}}"));
    return 0;
}