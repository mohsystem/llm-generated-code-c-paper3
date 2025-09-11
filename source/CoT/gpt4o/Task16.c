#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char *str, const char *ending) {
    if (str == NULL || ending == NULL) return false;
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    if (str_len < ending_len) return false;
    return strncmp(str + str_len - ending_len, ending, ending_len) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // 1
    printf("%d\n", solution("abc", "d"));  // 0
    printf("%d\n", solution("hello", "lo")); // 1
    printf("%d\n", solution("world", "ld")); // 1
    printf("%d\n", solution("java", "va"));  // 1
    return 0;
}