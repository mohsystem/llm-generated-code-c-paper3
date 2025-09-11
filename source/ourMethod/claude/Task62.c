
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    cJSON* root;
} JsonParser;

JsonParser* parse_and_get_root(const char* json_str) {
    if (json_str == NULL || strlen(json_str) == 0) {
        return NULL;
    }

    JsonParser* parser = (JsonParser*)malloc(sizeof(JsonParser));
    if (parser == NULL) {
        return NULL;
    }

    parser->root = cJSON_Parse(json_str);
    if (parser->root == NULL) {
        free(parser);
        return NULL;
    }

    if (!cJSON_IsObject(parser->root)) {
        cJSON_Delete(parser->root);
        free(parser);
        return NULL;
    }

    return parser;
}

void free_json_parser(JsonParser* parser) {
    if (parser != NULL) {
        if (parser->root != NULL) {
            cJSON_Delete(parser->root);
        }
        free(parser);
    }
}

int main() {
    // Test cases
    const char* test_cases[] = {
        "{\\"name\\":\\"John\\", \\"age\\":30}",
        "{\\"employees\\":[{\\"name\\":\\"Tom\\", \\"age\\":25},{\\"name\\":\\"Jane\\", \\"age\\":28}]}",
        "{}",
        "{\\"nested\\":{\\"key\\":\\"value\\"}}",
        "{\\"array\\":[1,2,3,4,5]}"
    };
    const int num_tests = 5;

    for (int i = 0; i < num_tests; i++) {
        printf("Test case %d:\\n", i + 1);
        JsonParser* parser = parse_and_get_root(test_cases[i]);
        
        if (parser != NULL) {
            char* printed = cJSON_Print(parser->root);
            if (printed != NULL) {
                printf("Root element: %s\\n", printed);
                free(printed);
            } else {
                printf("Error: Could not print JSON\\n");
            }
            free_json_parser(parser);
        } else {
            printf("Error: Invalid JSON format or memory allocation failed\\n");
        }
        printf("\\n");
    }

    return 0;
}
