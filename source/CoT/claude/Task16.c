
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len2 > len1) {
        return false;
    }
    
    return strcmp(str1 + len1 - len2, str2) == 0;
}

int main() {
    // Test cases
    printf("%d\\n", solution("abc", "bc")); // 1
    printf("%d\\n", solution("abc", "d")); // 0
    printf("%d\\n", solution("hello world", "world")); // 1
    printf("%d\\n", solution("python", "java")); // 0
    printf("%d\\n", solution("programming", "ming")); // 1
    return 0;
}
