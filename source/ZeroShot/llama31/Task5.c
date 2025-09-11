#include <stdio.h>
#include <string.h>

int persistence(int num) {
    int count = 0;
    while (num >= 10) {
        int product = 1;
        int temp = num;
        while (temp > 0) {
            product *= temp % 10;
            temp /= 10;
        }
        num = product;
        count++;
    }
    return count;
}

int main() {
    printf("%d\n", persistence(39));   // Output: 3
    printf("%d\n", persistence(999));  // Output: 4
    printf("%d\n", persistence(4));    // Output: 0
    printf("%d\n", persistence(25));   // Output: 2
    printf("%d\n", persistence(678));  // Output: 3
    return 0;
}