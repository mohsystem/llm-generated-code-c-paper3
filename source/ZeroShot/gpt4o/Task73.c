#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

bool is_valid_password(const char *password) {
    if (password == NULL) return false;
    const char *pattern = "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#\\$%\\^&\\*])(?=\\S+$).{8,}$";
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return false;

    ret = regexec(&regex, password, 0, NULL, 0);
    regfree(&regex);
    return ret == 0;
}

int main() {
    printf("%d\n", is_valid_password("Admin123!")); // 1
    printf("%d\n", is_valid_password("admin123!")); // 0
    printf("%d\n", is_valid_password("ADMIN123!")); // 0
    printf("%d\n", is_valid_password("Admin!"));    // 0
    printf("%d\n", is_valid_password("Admin123456")); // 0
    return 0;
}