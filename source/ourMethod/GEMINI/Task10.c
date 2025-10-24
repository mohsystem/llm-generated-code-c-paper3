#include <stdio.h>

/**
 * @brief Given two integers a and b, which can be positive or negative,
 * find the sum of all the integers between and including them and return it.
 * If the two numbers are equal return a or b.
 * Note: a and b are not ordered.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of all integers between a and b (inclusive).
 */
long long getSum(int a, int b) {
    if (a == b) {
        return a;
    }
    // Using long long to prevent potential overflow for large ranges
    long long start = (a < b) ? a : b;
    long long end = (a > b) ? a : b;
    
    // Arithmetic series sum formula: n * (first + last) / 2
    // where n is the number of terms (end - start + 1)
    return (end - start + 1) * (start + end) / 2;
}

int main() {
    // Test cases
    printf("getSum(1, 0) --> %lld\n", getSum(1, 0));       // Expected: 1
    printf("getSum(1, 2) --> %lld\n", getSum(1, 2));       // Expected: 3
    printf("getSum(-1, 2) --> %lld\n", getSum(-1, 2));     // Expected: 2
    printf("getSum(1, 1) --> %lld\n", getSum(1, 1));       // Expected: 1
    printf("getSum(-5, 5) --> %lld\n", getSum(-5, 5));     // Expected: 0
    return 0;
}