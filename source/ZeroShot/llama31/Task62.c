// task62.c
#include <cjson/cJSON.h>
#include <stdio.h>

int main() {
    const char* testCases[] = {
        "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}",
        "{\"id\":1, \"name\":\"Jane\", \"occupation\":\"Developer\"}",
        "{\"company\":{\"name\":\"ABC Inc\", \"address\":{\"street\":\"123 Main St\", \"city\":\"Anytown\"}}}",
        "{\"empty\":{}}",
        "{\"null\":null}"
    };

    for (int i = 0; i < 5; i++) {
        cJSON* root = cJSON_Parse(testCases[i]);
        if (root != NULL) {
            printf("Root Element: %s\n", cJSON_Print(root));
            cJSON_Delete(root);
        } else {
            printf("Error parsing JSON\n");
        }
    }

    return 0;
}