#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * Validates an ATM PIN.
 * A valid PIN must be a string containing exactly 4 or 6 digits.
 *
 * @param pin The string to validate.
 * @return true if the PIN is valid, false otherwise.
 */
bool validatePin(const char* pin) {
    // Rule #1: Ensure all input is validated. Check for NULL input.
    if (pin == NULL) {
        return false;
    }
    
    size_t len = strlen(pin);

    // Validate length
    if (len != 4 && len != 6) {
        return false;
    }
    
    // Rule #3: Ensure that all buffer operations strictly adhere to boundaries.
    // The loop is bounded by `len`, which was safely determined by `strlen`.
    for (size_t i = 0; i < len; ++i) {
        // isdigit expects an int; casting to unsigned char prevents issues
        // with negative char values on some systems.
        if (!isdigit((unsigned char)pin[i])) {
            return false;
        }
    }
    
    return true;
}

int main() {
    printf("Running C test cases...\n");
    const char* testCases[] = {"1234", "123456", "12345", "a234", "123"};
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (size_t i = 0; i < numTests; ++i) {
        printf("PIN: \"%s\" -> %s\n", testCases[i], validatePin(testCases[i]) ? "true" : "false");
    }
    
    return 0;
}