#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    if (str_len < ending_len) {
        return false;
    }
    return strncmp(str + str_len - ending_len, ending, ending_len) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // returns 1 (true)
    printf("%d\n", solution("abc", "d")); // returns 0 (false)
    printf("%d\n", solution("hello", "lo")); // returns 1 (true)
    printf("%d\n", solution("world", "ld!")); // returns 0 (false)
    printf("%d\n", solution("java", "")); // returns 1 (true)
    return 0;
}