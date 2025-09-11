#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cJSON.h>


cJSON* getRootElement(const char* jsonString) {
    if (jsonString == NULL || strlen(jsonString) == 0 || jsonString[strspn(jsonString, " \t\r\n")] == 0) {
      return NULL;
    }

    cJSON *root = cJSON_Parse(jsonString);
    if (root == NULL) {
      return NULL;
    }
    return root;
}


int main() {
    char* testCases[] = {
        "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}",
        "[1, 2, 3]",
        "{\"a\":{\"b\":{\"c\":\"d\"}}}",
        "{\"employees\":[{\"firstName\":\"John\", \"lastName\":\"Doe\"},{\"firstName\":\"Anna\", \"lastName\":\"Smith\"},{\"firstName\":\"Peter\", \"lastName\":\"Jones\"}]}",
        "   "
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        cJSON* root = getRootElement(testCases[i]);

        printf("Input: %s\n", testCases[i]);
        if(root == NULL)
        {
          printf("Root Element: null\n");
        }
        else {
           char* root_str = cJSON_Print(root);
           printf("Root Element: %s\n", root_str);
           free(root_str);
           cJSON_Delete(root);
        }

    }

    return 0;
}