
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool solution(const char* str, const char* ending) {
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    
    if (ending_len > str_len) {
        return false;
    }
    
    return strcmp(str + str_len - ending_len, ending) == 0;
}

int main() {
    // Test cases
    printf("%d\\n", solution("abc", "bc")); // 1
    printf("%d\\n", solution("abc", "d")); // 0
    printf("%d\\n", solution("samurai", "ai")); // 1
    printf("%d\\n", solution("ninja", "ja")); // 1
    printf("%d\\n", solution("sensei", "i")); // 1
    return 0;
}
