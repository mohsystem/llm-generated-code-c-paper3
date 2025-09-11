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
    printf("%d\n", persistence(39));  // Output: 3
    printf("%d\n", persistence(999));  // Output: 4
    printf("%d\n", persistence(4));  // Output: 0
    return 0;
}