#include <stdio.h>
#include <string.h>

int persistence(long long n) {
    int count = 0;
    while (n >= 10) {
        long long product = 1;
        char s[20];
        sprintf(s, "%lld", n);
        for (int i = 0; s[i] != '\0'; i++) {
            product *= (s[i] - '0');
        }
        n = product;
        count++;
    }
    return count;
}

int main() {
    printf("%d\n", persistence(39)); // Output: 3
    printf("%d\n", persistence(999)); // Output: 4
    printf("%d\n", persistence(4)); // Output: 0
    printf("%d\n", persistence(25)); // Output: 2
    printf("%d\n", persistence(77)); // Output: 4
    return 0;
}