#include <stdio.h>
#include <jansson.h>

char* getRootElement(char* jsonStr) {
    json_t *root = json_loads(jsonStr, 0, NULL);
    const char *key = json_object_iter_key(json_object_iter(root));
    char *rootElement = malloc(strlen(key) + 1);
    strcpy(rootElement, key);
    json_decref(root);
    return rootElement;
}

int main() {
    char* jsonStr = "{\"rootElement\": {\"key\": \"value\"}}";
    char* rootElement = getRootElement(jsonStr);
    printf("%s\n", rootElement);
    free(rootElement);
    return 0;
}