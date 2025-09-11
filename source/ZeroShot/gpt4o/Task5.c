#include <stdio.h>

int persistence(int num) {
    int count = 0;
    while (num >= 10) {
        int product = 1;
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
    printf("%d\n", persistence(25)); // 2
    printf("%d\n", persistence(444)); // 3
    return 0;
}