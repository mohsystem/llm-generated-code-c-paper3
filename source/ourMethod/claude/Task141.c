
#include <stdio.h>
#include <string.h>

void reverseString(char* str) {
    // Input validation
    if (str == NULL) {
        return;
    }
    
    int left = 0;
    int right = strlen(str) - 1;
    
    // Reverse by swapping characters from start and end
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main() {
    // Test cases with fixed size buffers to prevent overflow
    char test1[] = "hello";
    char test2[] = "";
    char test3[] = "a";
    char test4[] = "12345";
    char test5[] = "Hello World!";
    
    char* tests[] = {test1, test2, test3, test4, test5};
    
    for (int i = 0; i < 5; i++) {
        printf("Input: \\"%s\\"\\n", tests[i]);
        reverseString(tests[i]);
        printf("Output: \\"%s\\"\\n\\n", tests[i]);
    }
    
    return 0;
}
