#include <stdio.h>
#include <string.h>

int solution(const char *str, const char *ending) {
    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);
    return str_len >= ending_len && strncmp(str + str_len - ending_len, ending, ending_len) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // returns 1 (true)
    printf("%d\n", solution("abc", "d")); // returns 0 (false)
    printf("%d\n", solution("abcd", "cd")); // returns 1 (true)
    printf("%d\n", solution("abcd", "bc")); // returns 0 (false)
    printf("%d\n", solution("abcd", "d")); // returns 1 (true)
    return 0;
}