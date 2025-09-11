#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool validatePin(const char* pin) {
    int len = strlen(pin);
    if (len == 4 || len == 6) {
        for (int i = 0; i < len; i++) {
            if (!isdigit(pin[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    printf("%d\n", validatePin("1234"));   // 1 (true)
    printf("%d\n", validatePin("12345"));  // 0 (false)
    printf("%d\n", validatePin("a234"));   // 0 (false)
    printf("%d\n", validatePin("123456")); // 1 (true)
    printf("%d\n", validatePin("12345a")); // 0 (false)
    return 0;
}