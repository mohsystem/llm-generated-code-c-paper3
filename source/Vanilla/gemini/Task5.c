#include <stdio.h>
#include <string.h>

int persistence(long long n) {
    int count = 0;
    while (n >= 10) {
        long long product = 1;
        char s[20];
        sprintf(s, "%lld", n);
        for (int i = 0; i < strlen(s); i++) {
            product *= (s[i] - '0');
        }
        n = product;
        count++;
    }
    return count;
}

int main() {
    printf("%d\n", persistence(39)); // 3
    printf("%d\n", persistence(999)); // 4
    printf("%d\n", persistence(4)); // 0
    printf("%d\n", persistence(25)); // 2
    printf("%d\n", persistence(77)); // 4
    return 0;
}