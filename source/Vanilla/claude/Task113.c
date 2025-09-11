
#include <stdio.h>
#include <string.h>

char* concatenateStrings(char* result, int count, ...) {
    va_list args;
    va_start(args, count);
    
    result[0] = '\\0';
    for(int i = 0; i < count; i++) {
        strcat(result, va_arg(args, char*));
    }
    
    va_end(args);
    return result;
}

int main() {
    char result[1000];
    
    // Test case 1
    printf("%s\\n", concatenateStrings(result, 3, "Hello", " ", "World"));
    
    // Test case 2
    printf("%s\\n", concatenateStrings(result, 4, "Java", "Python", "CPP", "C"));
    
    // Test case 3
    printf("%s\\n", concatenateStrings(result, 5, "One", " ", "Two", " ", "Three"));
    
    // Test case 4
    printf("%s\\n", concatenateStrings(result, 3, "Programming", "-", "Languages"));
    
    // Test case 5
    printf("%s\\n", concatenateStrings(result, 5, "Test", "-", "Case", "-", "Five"));
    
    return 0;
}
