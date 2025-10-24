#include <stdio.h>
#include <errno.h>

/**
 * @brief Calculates the factorial of a non-negative integer.
 *
 * The input is restricted to the range [0, 20] to prevent long long overflow.
 *
 * @param n The non-negative integer.
 * @param result A pointer to a long long to store the factorial result.
 * @return 0 on success, -1 on failure (and errno is set).
 */
int factorial(int n, long long* result) {
    // Rule #4: Validate input range.
    if (n < 0 || n > 20) {
        // Using EDOM (domain error) for out-of-range mathematical input.
        errno = EDOM; 
        return -1;
    }

    if (result == NULL) {
        errno = EINVAL; // Invalid argument (null pointer)
        return -1;
    }

    *result = 1LL;
    for (int i = 2; i <= n; ++i) {
        *result *= i;
    }

    return 0;
}

int main() {
    // 5 test cases including edge/error cases
    int testCases[] = {0, 1, 5, 10, -1, 21};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    printf("Running test cases for factorial calculation:\n");
    for (int i = 0; i < numTestCases; ++i) {
        int testValue = testCases[i];
        long long result;

        printf("-------------------------------------\n");
        printf("Calculating factorial for: %d\n", testValue);
        
        // Reset errno before the call
        errno = 0; 
        if (factorial(testValue, &result) == 0) {
            printf("Result: %lld\n", result);
        } else {
            // Check return values of functions.
            if (errno == EDOM) {
                fprintf(stderr, "Error: Input must be an integer between 0 and 20.\n");
            } else {
                // For other potential errors
                perror("An unexpected error occurred");
            }
        }
    }
    printf("-------------------------------------\n");

    return 0;
}