#include <stdio.h>
#include <cjson/cJSON.h>

char* extractRootElement(const char* jsonString) {
    cJSON* jsonObject = cJSON_Parse(jsonString);
    cJSON* root = jsonObject->child;
    char* rootElement = root->string;
    cJSON_Delete(jsonObject);
    return rootElement;
}

int main() {
    const char* testCases[] = {"{\"key1\": \"value1\"}", "{\"key2\": {\"key3\": \"value3\"}}", "{\"key4\": [1, 2, 3]}", "{\"key5\": null}", "{\"key6\": true}"};
    for (int i = 0; i < 5; i++) {
        printf("Root element of %s is: %s\n", testCases[i], extractRootElement(testCases[i]));
    }
    return 0;
}