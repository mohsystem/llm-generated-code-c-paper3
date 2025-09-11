
#include <stdio.h>
#include <stdlib.h>

int findGCD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    // Test cases
    printf("%d\\n", findGCD(48, 36));  // 12
    printf("%d\\n", findGCD(54, 24));  // 6
    printf("%d\\n", findGCD(7, 13));   // 1
    printf("%d\\n", findGCD(48, -36)); // 12
    printf("%d\\n", findGCD(0, 5));    // 5
    return 0;
}
