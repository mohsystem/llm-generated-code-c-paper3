int main() {
    const char* testCases[] = {
        "{\"key\":\"value\"}",
        "{\"array\":[1,2,3]}",
        "{\"object\":{\"nestedKey\":\"nestedValue\"}}"
    };
    for (int i = 0; i < 3; ++i) {
        cJSON* root = cJSON_Parse(testCases[i]);
        if (root == NULL) {
            fprintf(stderr, "Error parsing JSON\n");
            return EXIT_FAILURE;
        }
        printf("Root Element: %s\n", cJSON_Print(root));
        cJSON_Delete(root);
    }
    return EXIT_SUCCESS;
}