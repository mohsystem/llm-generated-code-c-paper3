#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char* str, const char* ending) {
    if (!str || !ending) return false;
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    if (ending_len > str_len) return false;
    return strcmp(str + str_len - ending_len, ending) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // true
    printf("%d\n", solution("abc", "d"));  // false
    printf("%d\n", solution("hello", "lo")); // true
    printf("%d\n", solution("hello", "")); // true
    printf("%d\n", solution("", "a"));    // false
    return 0;
}