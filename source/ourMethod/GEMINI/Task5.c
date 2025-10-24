#include <stdio.h>

/**
 * @brief Calculates the multiplicative persistence of a positive number.
 * 
 * @param num A positive long long integer.
 * @return The number of times digits must be multiplied to reach a single digit.
 */
int persistence(long long num) {
    int count = 0;
    while (num >= 10) {
        count++;
        long long product = 1;
        long long temp = num;
        while (temp > 0) {
            product *= temp % 10;
            temp /= 10;
        }
        num = product;
    }
    return count;
}

int main() {
    // 5 test cases
    printf("Input: 39, Output: %d\n", persistence(39));      // Expected: 3
    printf("Input: 999, Output: %d\n", persistence(999));    // Expected: 4
    printf("Input: 4, Output: %d\n", persistence(4));        // Expected: 0
    printf("Input: 25, Output: %d\n", persistence(25));      // Expected: 2
    printf("Input: 679, Output: %d\n", persistence(679));    // Expected: 5
    return 0;
}