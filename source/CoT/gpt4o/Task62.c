#include <stdio.h>
#include <string.h>
#include <json-c/json.h> // Ensure you have the json-c library available

const char* getRootElement(const char* jsonString) {
    struct json_object *parsed_json;
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    parsed_json = json_tokener_parse(jsonString);
    it = json_object_iter_begin(parsed_json);
    itEnd = json_object_iter_end(parsed_json);

    const char* rootKey = NULL;
    if (!json_object_iter_equal(&it, &itEnd)) {
        rootKey = json_object_iter_peek_name(&it);
    }

    return rootKey;
}

int main() {
    printf("%s\n", getRootElement("{\"key1\": \"value1\"}"));
    printf("%s\n", getRootElement("{\"key2\": {\"subkey\": \"value\"}}"));
    printf("%s\n", getRootElement("{\"key3\": [1, 2, 3]}"));
    printf("%s\n", getRootElement("{\"key4\": \"value4\", \"key5\": \"value5\"}"));
    printf("%s\n", getRootElement("{\"key6\": {\"subkey\": {\"subsubkey\": \"value\"}}}"));
    return 0;
}