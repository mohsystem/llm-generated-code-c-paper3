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
    printf("%s\n", solution("abc", "bc") ? "true" : "false"); // true
    printf("%s\n", solution("abc", "d") ? "true" : "false"); // false
    printf("%s\n", solution("abc", "") ? "true" : "false"); // true
    printf("%s\n", solution("", "bc") ? "true" : "false"); // false
    char* s = ""; // Initialize to handle potential null
    printf("%s\n", solution(s, "bc") ? "true" : "false"); // false, demonstrates handling null by using "" instead

    return 0;
}