#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int num1, num2;
    printf("Enter two numbers:\n");
    scanf("%d %d", &num1, &num2);

    int result = gcd(num1, num2);
    printf("GCD of %d and %d is: %d\n", num1, num2, result);


    printf("Test case 1: GCD(48, 18) = %d\n", gcd(48, 18)); // Expected: 6
    printf("Test case 2: GCD(12, 18) = %d\n", gcd(12, 18)); // Expected: 6
    printf("Test case 3: GCD(7, 13) = %d\n", gcd(7, 13));   // Expected: 1
    printf("Test case 4: GCD(100, 0) = %d\n", gcd(100, 0));  // Expected: 100
    printf("Test case 5: GCD(0, 50) = %d\n", gcd(0, 50));  // Expected: 50

    return 0;
}