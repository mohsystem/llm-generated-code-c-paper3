#include <stdio.h>
#include <string.h>

void reverseString(const char* input, char* output) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - i - 1];
    }
    output[len] = '\0';
}

int main() {
    char output[100];
    
    reverseString("hello", output);
    printf("%s\n", output);  // Test case 1
    
    reverseString("world", output);
    printf("%s\n", output);  // Test case 2
    
    reverseString("java", output);
    printf("%s\n", output);  // Test case 3
    
    reverseString("python", output);
    printf("%s\n", output);  // Test case 4
    
    reverseString("cpp", output);
    printf("%s\n", output);  // Test case 5
    
    return 0;
}