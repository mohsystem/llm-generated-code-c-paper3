#include <stdio.h>
#include <cjson/cJSON.h>

void parseJson(const char* json_string) {
    cJSON* json = cJSON_Parse(json_string);
    if (json != NULL) {
        if (cJSON_IsObject(json)) {
            cJSON* child = cJSON_GetObjectItem(json, cJSON_GetObjectItem(json, NULL)->string);
            printf("Root Element: %s\n", cJSON_GetObjectItem(json, NULL)->string);
        }
        cJSON_Delete(json);
    } else {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
}

int main() {
    const char* test_cases[] = {
        "{\"name\": \"John Doe\", \"age\": 30, \"email\": \"john.doe@example.com\"}",
        "{\"city\": \"New York\", \"country\": \"USA\"}",
        "{\"students\": [{\"name\": \"Alice\", \"age\": 20}, {\"name\": \"Bob\", \"age\": 21}]}",
        "{\"empty\": {}}",
        "{\"null\": null}"
    };

    for (int i = 0; i < 5; i++) {
        parseJson(test_cases[i]);
    }

    return 0;
}