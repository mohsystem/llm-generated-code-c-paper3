
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void processUserInput(const char* input, char* output) {
    if (input == NULL || strlen(input) == 0) {
        strcpy(output, "Invalid input");
        return;
    }
    
    // Sanitize input
    int j = 0;
    for (int i = 0; input[i] != '\\0' && j < MAX_LENGTH - 1; i++) {
        if (isalnum(input[i]) || isspace(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\\0';
    
    // Reverse the string
    reverseString(output);
}

int main() {
    const char* tests[] = {
        "Hello World!",
        "Test@123",
        "",
        "ThisIsAVeryLongInputStringThatShouldBeTruncated",
        "<script>alert('xss')</script>"
    };
    
    char output[MAX_LENGTH];
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        processUserInput(tests[i], output);
        printf("Output: %s\\n\\n", output);
    }
    
    return 0;
}
