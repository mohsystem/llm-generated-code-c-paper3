#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

const char* findRootElement(const char* jsonString) {
    struct json_object *parsed_json = json_tokener_parse(jsonString);
    struct lh_table *object_table = json_object_get_object(parsed_json);
    struct lh_entry *entry = object_table->head;
    return (const char *)entry->k;
}

int main() {
    printf("%s\n", findRootElement("{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}"));
    printf("%s\n", findRootElement("{\"employee\":{\"name\":\"Anna\",\"age\":28,\"city\":\"London\"}}"));
    printf("%s\n", findRootElement("{\"menu\":{\"id\":\"file\",\"value\":\"File\"}}"));
    printf("%s\n", findRootElement("{\"widget\":{\"debug\":\"on\",\"window\":{\"title\":\"Sample Widget\"}}}"));
    printf("%s\n", findRootElement("{\"library\":{\"books\":[],\"staff\":{}}}"));
    return 0;
}