#include <stdio.h>
#include <jansson.h>

json_t* get_root_element(const char* json_str) {
    json_t* json_obj = json_loads(json_str, 0, NULL);
    return json_obj;
}

int main() {
    const char* json_str = "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";
    json_t* root = get_root_element(json_str);
    char* serialized_root = json_dumps(root, JSON_INDENT(4));
    printf("%s\n", serialized_root);
    free(serialized_root);
    json_decref(root);
    return 0;
}