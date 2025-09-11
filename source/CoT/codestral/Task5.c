#include<stdio.h>

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
    printf("%d\n", persistence(39)); // Outputs: 3
    printf("%d\n", persistence(999)); // Outputs: 4
    printf("%d\n", persistence(4)); // Outputs: 0
    return 0;
}