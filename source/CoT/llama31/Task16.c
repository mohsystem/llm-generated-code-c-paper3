#include <stdio.h>
#include <string.h>

bool solution(const char* str, const char* ending) {
    if (str == NULL || ending == NULL) {
        printf("Error: Input strings cannot be NULL\n");
        return false;
    }
    size_t lenStr = strlen(str);
    size_t lenEnding = strlen(ending);
    if (lenEnding > lenStr) {
        return false;
    }
    return strcmp(str + lenStr - lenEnding, ending) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // 1 (true)
    printf("%d\n", solution("abc", "d")); // 0 (false)
    printf("%d\n", solution("abcde", "de")); // 1 (true)
    printf("%d\n", solution("abcde", "e")); // 1 (true)
    printf("%d\n", solution("abcde", "abc")); // 0 (false)
    return 0;
}