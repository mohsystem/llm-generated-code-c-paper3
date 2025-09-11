#include <stdio.h>

int persistence(long num) {
    int times = 0;
    while (num >= 10) {
        long temp = 1;
        while (num > 0) {
            temp *= num % 10;
            num /= 10;
        }
        num = temp;
        times++;
    }
    return times;
}

int main() {
    printf("%d\n", persistence(39)); // Outputs: 3
    printf("%d\n", persistence(999)); // Outputs: 4
    printf("%d\n", persistence(4)); // Outputs: 0
    return 0;
}