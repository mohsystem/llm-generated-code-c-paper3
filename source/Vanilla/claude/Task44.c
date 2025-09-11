
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

void processInput(const char* input, char* output) {
    if(input == NULL || strlen(input) == 0) {
        strcpy(output, "Invalid input");
        return;
    }
    
    int j = 0;
    char temp[MAX_LENGTH];
    
    // Remove special characters and numbers
    for(int i = 0; input[i]; i++) {
        if(isalpha(input[i]) || isspace(input[i])) {
            temp[j++] = toupper(input[i]);
        }
    }
    temp[j] = '\\0';
    
    // Reverse string
    int len = strlen(temp);
    for(int i = 0; i < len; i++) {
        output[i] = temp[len-1-i];
    }
    output[len] = '\\0';
}

int main() {
    const char* tests[] = {
        "Hello World!",
        "Test123",
        "",
        "Special@#$Characters",
        "AbCdEf 123"
    };
    
    char output[MAX_LENGTH];
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        processInput(tests[i], output);
        printf("Output: %s\\n\\n");
    }
    
    return 0;
}
