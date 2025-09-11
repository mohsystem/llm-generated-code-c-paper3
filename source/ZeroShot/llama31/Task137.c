#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidInput(const char* input) {
    // Allowlist validation for product ID (e.g., numeric only)
    while (*input != '\0') {
        if (!isdigit(*input)) {
            return false;
        }
        input++;
    }
    return true;
}

void testCases() {
    printf("Test Case 1: Valid input\n");
    printf("%s\n", isValidInput("12345") ? "Valid" : "Invalid");

    printf("Test Case 2: Invalid input\n");
    printf("%s\n", isValidInput("abcde") ? "Valid" : "Invalid");

    printf("Test Case 3: Empty input\n");
    printf("%s\n", isValidInput("") ? "Valid" : "Invalid");

    printf("Test Case 4: Special characters\n");
    printf("%s\n", isValidInput("12345") ? "Valid" : "Invalid");

    printf("Test Case 5: Negative number\n");
    printf("%s\n", isValidInput("-12345") ? "Valid" : "Invalid");
}

int main() {
    char input[100];
    printf("Enter the product ID: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character
    input[strcspn(input, "\n")] = 0;

    // Input validation
    if (isValidInput(input)) {
        printf("Product ID: %s\n", input);
        // Simulate querying the product table
        printf("Product Details: Product ID %s found.\n", input);
    } else {
        printf("Invalid input. Please enter a valid product ID.\n");
    }

    // Test cases
    testCases();

    return 0;
}