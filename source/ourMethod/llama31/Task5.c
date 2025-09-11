#include <stdio.h>

int multiplyDigits(int num) {
    int product = 1;
    while (num > 0) {
        product *= num % 10;
        num /= 10;
    }
    return product;
}

int persistence(int num) {
    int count = 0;
    while (num >= 10) {
        num = multiplyDigits(num);
        count++;
    }
    return count;
}

int main() {
    printf("%d\n", persistence(39)); // Output: 3
    printf("%d\n", persistence(999)); // Output: 4
    printf("%d\n", persistence(4)); // Output: 0
    printf("%d\n", persistence(25)); // Output: 2
    printf("%d\n", persistence(10)); // Output: 1
    return 0;
}