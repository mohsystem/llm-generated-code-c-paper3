#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h" // Assuming you have the cJSON library

// Function to get the root element of a JSON string
cJSON* getRootElement(const char* jsonString) {
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return NULL;
    }


    if (cJSON_IsObject(json)) {
        if (json->child != NULL) {  // Check if the object is not empty
            cJSON *first_child = json->child;
            cJSON *root = cJSON_Duplicate(first_child->value, 1);
            return root;
        } else {
             // Handle empty JSON object case
            return NULL;  // You might want to handle this differently
        }

    } else if (cJSON_IsArray(json)) {

            return json;

    } else {
      // Invalid JSON type
        return NULL;
    }

}



int main() {
    char test1[] = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    char test2[] = "[1, 2, 3]";
    char test3[] = "{\"a\":{\"b\":{\"c\":1}}}";
    char test4[] = "[]";
    char test5[] = "{}";

    cJSON *root1 = getRootElement(test1);
    cJSON *root2 = getRootElement(test2);
    cJSON *root3 = getRootElement(test3);
    cJSON *root4 = getRootElement(test4);
    cJSON *root5 = getRootElement(test5);



    if(root1 != NULL) { char *string = cJSON_Print(root1); printf("%s\n", string); free(string);} else { printf("null\n"); }
    if(root2 != NULL) { char *string = cJSON_Print(root2); printf("%s\n", string); free(string);} else { printf("null\n"); }
    if(root3 != NULL) { char *string = cJSON_Print(root3); printf("%s\n", string); free(string);} else { printf("null\n"); }
    if(root4 != NULL) { char *string = cJSON_Print(root4); printf("%s\n", string); free(string);} else { printf("null\n"); }
    if(root5 != NULL) { char *string = cJSON_Print(root5); printf("%s\n", string); free(string);} else { printf("null\n"); }



   if (root1) cJSON_Delete(root1);
    if (root2) cJSON_Delete(root2);
    if (root3) cJSON_Delete(root3);
    if (root4) cJSON_Delete(root4);
     if (root5) cJSON_Delete(root5);
    return 0;
}