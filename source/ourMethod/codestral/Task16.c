#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool solution(const char* str, const char* ending) {
    if (str == NULL || ending == NULL)
        return false;

    size_t str_len = strlen(str);
    size_t ending_len = strlen(ending);

    if (str_len < ending_len)
        return false;

    return strcmp(str + str_len - ending_len, ending) == 0;
}

int main() {
    printf("%d\n", solution("abc", "bc")); // returns 1 (true)
    printf("%d\n", solution("abc", "d")); // returns 0 (false)
    return 0;
}