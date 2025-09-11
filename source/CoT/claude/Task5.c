
#include <stdio.h>

int persistence(long long num) {
    if (num < 10) return 0;
    
    int count = 0;
    while (num >= 10) {
        long long product = 1;
        while (num > 0) {
            product *= (num % 10);
            num /= 10;
        }
        num = product;
        count++;
    }
    return count;
}

int main() {
    printf("%d\\n", persistence(39));   // 3
    printf("%d\\n", persistence(999));  // 4
    printf("%d\\n", persistence(4));    // 0
    printf("%d\\n", persistence(25));   // 2
    printf("%d\\n", persistence(777));  // 4
    return 0;
}
