#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* processString(const char* input) {
    if (input == NULL) {
        char* emptyStr = (char*)malloc(1);
        if(emptyStr == NULL) return NULL;
        emptyStr[0] = '\0';
        return emptyStr;
    }
    size_t len = strlen(input);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL; 
    strcpy(result, input);
    return result;
}

int main() {
    char* result1 = processString("Test1");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    char* result2 = processString("Test2");
     if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char* result3 = processString("Test3");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    char* result4 = processString("Test4");
    if (result4 != NULL) {
       printf("%s\n", result4);
        free(result4);
    }

    char *result5 = processString(NULL);
    if(result5 != NULL){
        printf("%s\n", result5);
        free(result5);
    }
    

    return 0;
}