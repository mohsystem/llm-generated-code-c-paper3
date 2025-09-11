#include <stdio.h>

int persistence(long num) {
    int count = 0;
    while (num >= 10) {
        long product = 1;
        while (num > 0) {
            product *= num % 10;
            num /= 10;
        }
        num = product;
        count++;
    }
    return count;
}

int main() {
    printf("%d\n", persistence(39)); // 3
    printf("%d\n", persistence(999)); // 4
    printf("%d\n", persistence(4)); // 0
    return 0;
}