#include <stdio.h>
#include <string.h>

bool solution(const char* str, const char* suffix) {
    size_t strLen = strlen(str);
    size_t suffixLen = strlen(suffix);
    if (strLen < suffixLen) return false;
    return strcmp(str + strLen - suffixLen, suffix) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // 1 (true)
    printf("%d\n", solution("abc", "d")); // 0 (false)
    printf("%d\n", solution("hello world", "world")); // 1 (true)
    printf("%d\n", solution("hello world", "hello")); // 0 (false)
    printf("%d\n", solution("test", "test")); // 1 (true)
    return 0;
}