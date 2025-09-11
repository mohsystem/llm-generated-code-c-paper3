
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* toJadenCase(const char* phrase) {
    // Check for NULL or empty string
    if (phrase == NULL || strlen(phrase) == 0) {
        return NULL;
    }
    
    // Allocate memory for result
    char* result = (char*)malloc(strlen(phrase) + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // Copy input to result
    strcpy(result, phrase);
    
    // Capitalize first character
    if (result[0] != '\\0') {
        result[0] = toupper((unsigned char)result[0]);
    }
    
    // Process rest of the string
    for (size_t i = 1; result[i] != '\\0'; i++) {
        if (result[i - 1] == ' ' && result[i] != '\\0') {
            result[i] = toupper((unsigned char)result[i]);
        }
    }
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "How can mirrors be real if our eyes aren't real",
        "School Is The Tool To Brainwash The Youth",
        "if everybody in the world dropped out of school we would have a much more intelligent society",
        "All The Rules In This World Were Made By Someone No Smarter Than You",
        NULL
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "NULL");
        char* result = toJadenCase(tests[i]);
        printf("Output: %s\\n\\n", result ? result : "NULL");
        free(result);  // Free allocated memory
    }
    
    return 0;
}
