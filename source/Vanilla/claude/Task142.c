
#include <stdio.h>

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    printf("%d\\n", findGCD(48, 36));  // 12
    printf("%d\\n", findGCD(54, 24));  // 6
    printf("%d\\n", findGCD(7, 13));   // 1
    printf("%d\\n", findGCD(45, 75));  // 15
    printf("%d\\n", findGCD(100, 80)); // 20
    return 0;
}
