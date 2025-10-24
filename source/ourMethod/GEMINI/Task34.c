#include <stdio.h>
#include <stdbool.h>

// Helper function to calculate integer power safely and avoid double precision issues.
long long power(int base, int exp) {
    long long result = 1;
    if (base == 0) return 0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

/**
 * @brief Checks if a given number is a Narcissistic Number (Armstrong Number).
 * A number is narcissistic if it is the sum of its own digits, each raised to
 * the power of the number of digits.
 *
 * @param number The positive integer to check.
 * @return true if the number is narcissistic, false otherwise.
 */
bool isNarcissistic(int number) {
    // Count number of digits
    int num_digits = 0;
    int temp = number;
    if (temp == 0) {
        num_digits = 1;
    } else {
        while (temp > 0) {
            temp /= 10;
            num_digits++;
        }
    }

    // Calculate sum of powers of digits
    long long sum = 0;
    temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        sum += power(digit, num_digits);
        temp /= 10;
    }

    return sum == (long long)number;
}

int main() {
    // 5 test cases
    printf("isNarcissistic(153): %s\n", isNarcissistic(153) ? "true" : "false");   // Expected: true
    printf("isNarcissistic(1652): %s\n", isNarcissistic(1652) ? "true" : "false"); // Expected: false
    printf("isNarcissistic(7): %s\n", isNarcissistic(7) ? "true" : "false");      // Expected: true
    printf("isNarcissistic(371): %s\n", isNarcissistic(371) ? "true" : "false");   // Expected: true
    printf("isNarcissistic(123): %s\n", isNarcissistic(123) ? "true" : "false");   // Expected: false
    return 0;
}