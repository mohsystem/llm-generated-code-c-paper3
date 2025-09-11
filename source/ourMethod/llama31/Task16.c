#include <stdio.h>
#include <string.h>

bool solution(const char* str1, const char* str2) {
    // Check if str1 is NULL or str2 is NULL to avoid segmentation fault
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    // Check if str2 is longer than str1 to avoid out_of_range error
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len2 > len1) {
        return false;
    }
    // Use memcmp to check if str1 ends with str2
    return memcmp(str1 + len1 - len2, str2, len2) == 0;
}

int main() {
    // Test cases
    printf("%d\n", solution("abc", "bc"));   // 1 (true)
    printf("%d\n", solution("abc", "d"));    // 0 (false)
    printf("%d\n", solution("abc", "abc"));  // 1 (true)
    printf("%d\n", solution("abc", "abcd")); // 0 (false)
    printf("%d\n", solution(NULL, "bc"));     // 0 (false)
    return 0;
}