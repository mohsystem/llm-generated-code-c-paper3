// C with bool
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char* str, const char* ending) {
    size_t strLen = strlen(str);
    size_t endingLen = strlen(ending);
    if (strLen < endingLen) return false;
    return strcmp(str + strLen - endingLen, ending) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // 1 (true)
    printf("%d\n", solution("abc", "d")); // 0 (false)
    printf("%d\n", solution("hello", "lo")); // 1 (true)
    printf("%d\n", solution("hello", "ll")); // 0 (false)
    printf("%d\n", solution("abcde", "de")); // 1 (true)
    return 0;
}