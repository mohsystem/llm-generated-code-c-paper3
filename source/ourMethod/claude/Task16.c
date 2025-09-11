
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char* str, const char* ending) {
    // Handle null inputs
    if (str == NULL || ending == NULL) {
        return false;
    }
    
    // Handle empty ending
    if (ending[0] == '\\0') {
        return true;
    }
    
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    
    // Check if ending is longer than the string
    if (ending_len > str_len) {
        return false;
    }
    
    // Compare the ending
    return strcmp(str + str_len - ending_len, ending) == 0;
}

int main() {
    // Test cases
    printf("%d\\n", solution("abc", "bc"));     // 1 (true)
    printf("%d\\n", solution("abc", "d"));      // 0 (false)
    printf("%d\\n", solution("", ""));          // 1 (true)
    printf("%d\\n", solution("abc", ""));       // 1 (true)
    printf("%d\\n", solution("abc", "abc"));    // 1 (true)
    return 0;
}
