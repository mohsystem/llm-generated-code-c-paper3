
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK 100
#define MAX_ELEMENT 256

char* findRootElement(const char* jsonStr) {
    static char result[MAX_ELEMENT];
    if (!jsonStr || strlen(jsonStr) == 0) {
        result[0] = '\\0';
        return result;
    }
    
    char stack[MAX_STACK][MAX_ELEMENT];
    int stackTop = -1;
    char currentElement[MAX_ELEMENT];
    int currentLen = 0;
    bool inQuotes = false;
    
    for (int i = 0; jsonStr[i] != '\\0'; i++) {
        char c = jsonStr[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
            continue;
        }
        
        if (!inQuotes) {
            if (c == '{' || c == '[') {
                if (currentLen > 0) {
                    currentElement[currentLen] = '\\0';
                    stackTop++;
                    strcpy(stack[stackTop], currentElement);
                    currentLen = 0;
                }
            }
            else if (c == ':' || c == ',' || c == '}' || c == ']') {
                if (currentLen > 0) {
                    currentLen = 0;
                }
            }
            else {
                currentElement[currentLen++] = c;
            }
        }
        else {
            currentElement[currentLen++] = c;
        }
    }
    
    if (stackTop >= 0) {
        strcpy(result, stack[stackTop]);
    } else {
        result[0] = '\\0';
    }
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "{\\"root\\": {\\"child\\": \\"value\\"}}",
        "{\\"data\\": [1,2,3]}",
        "[]",
        "{}",
        "{\\"firstLevel\\": {\\"secondLevel\\": {\\"thirdLevel\\": \\"value\\"}}}"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Test %d: %s\\n", i+1, findRootElement(tests[i]));
    }
    
    return 0;
}
