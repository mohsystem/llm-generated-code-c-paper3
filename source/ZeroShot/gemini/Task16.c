#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    if (str == NULL || ending == NULL) {
        return false;
    }
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    if (ending_len > str_len) {
        return false;
    }
    return strcmp(str + str_len - ending_len, ending) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // true (1)
    printf("%d\n", solution("abc", "d")); // false (0)
    printf("%d\n", solution("abcde", "cde")); // true (1)
    printf("%d\n", solution("abc", "abc")); // true (1)
    printf("%d\n", solution("abc", "")); // true (1)
    return 0;
}