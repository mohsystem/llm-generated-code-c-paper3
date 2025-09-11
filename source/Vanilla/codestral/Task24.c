#include<stdio.h>
#include<string.h>
#include<ctype.h>

int validatePin(char* pin) {
    int len = strlen(pin);
    if (len != 4 && len != 6)
        return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(pin[i]))
            return 0;
    }
    return 1;
}

int main() {
    printf("%d\n", validatePin("1234"));   // -->  true
    printf("%d\n", validatePin("12345"));  // -->  false
    printf("%d\n", validatePin("a234"));   // -->  false
    printf("%d\n", validatePin("123456")); // -->  true
    printf("%d\n", validatePin("1234567")); // -->  false
    return 0;
}