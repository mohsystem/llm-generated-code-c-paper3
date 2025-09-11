
#include <stdio.h>
#include <string.h>

void handleInput(char* result, const char* input, int bufferSize) {
    if (input == NULL || bufferSize <= 0) {
        result[0] = '\\0';
        return;
    }
    
    int inputLen = strlen(input);
    int copyLen = (inputLen < bufferSize) ? inputLen : bufferSize;
    
    strncpy(result, input, copyLen);
    result[copyLen] = '\\0';
}

int main() {
    char result[100];
    
    // Test cases
    handleInput(result, "Hello World", 5);
    printf("%s\\n", result);  // "Hello"
    
    handleInput(result, "Test", 10);
    printf("%s\\n", result);  // "Test"
    
    handleInput(result, "Programming", 4);
    printf("%s\\n", result);  // "Prog"
    
    handleInput(result, "", 5);
    printf("%s\\n", result);  // ""
    
    handleInput(result, "C", 0);
    printf("%s\\n", result);  // ""
    
    return 0;
}
