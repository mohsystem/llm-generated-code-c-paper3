#include <stdio.h>
#include <string.h>
#include <jsmn.h>

int deserialize(const char *json_str, jsmntok_t **tokens) {
    jsmn_parser parser;
    jsmn_init(&parser);

    int token_count = jsmn_parse(&parser, json_str, strlen(json_str), NULL, 0);
    if (token_count < 0) {
        return -1;
    }

    *tokens = malloc(sizeof(jsmntok_t) * token_count);
    jsmn_init(&parser);
    jsmn_parse(&parser, json_str, strlen(json_str), *tokens, token_count);
    return 0;
}

int main() {
    const char *test_cases[] = {"{\"key\": \"value\"}", "{\"array\": [1, 2, 3]}", "{}", "null", "{\"object\": {\"key\": \"value\"}}"};
    for (int i = 0; i < 5; i++) {
        jsmntok_t *tokens;
        deserialize(test_cases[i], &tokens);
        free(tokens);
    }
    return 0;
}