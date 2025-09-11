
#include <stdio.h>
#include <string.h>

void reverseString(const char* input, char* output) {
    if (input == NULL || output == NULL) return;
    
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - 1 - i];
    }
    output[len] = '\\0';
}

int main() {
    const char* tests[] = {
        "Hello World",
        "Programming",
        "12345",
        "",
        "a"
    };
    
    char output[1000];  // Assuming max string length of 999
    
    for (int i = 0; i < 5; i++) {
        printf("Original: %s\\n", tests[i]);
        reverseString(tests[i], output);
        printf("Reversed: %s\\n\\n", output);
    }
    
    return 0;
}
