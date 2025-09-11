#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    size_t len_str = strlen(str);
    size_t len_ending = strlen(ending);
    if (len_str >= len_ending) {
        return (0 == strcmp(str + len_str - len_ending, ending));
    } else {
        return false;
    }
}

int main() {
    printf("%d\n", solution("abc", "bc")); // 1 (true)
    printf("%d\n", solution("abc", "d")); // 0 (false)
    printf("%d\n", solution("abcd", "cd")); // 1 (true)
    printf("%d\n", solution("abcd", "de")); // 0 (false)
    printf("%d\n", solution("", "")); // 1 (true)
    return 0;
}