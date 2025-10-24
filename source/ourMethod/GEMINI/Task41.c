#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

/**
 * @brief Safely processes a string by copying it to a destination buffer.
 *
 * This function uses snprintf to copy the source string to the destination
 * buffer. snprintf is safe against buffer overflows because it takes the
 * buffer size as an argument and will not write more characters than the
 * size allows, always ensuring the destination is null-terminated.
 *
 * @param dest The destination buffer.
 * @param dest_size The total size of the destination buffer.
 * @param src The source string to process/copy.
 */
void processString(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }

    // Use snprintf for a safe copy. It prevents buffer overflows by respecting
    // dest_size and guarantees null-termination.
    int written = snprintf(dest, dest_size, "%s", src);

    // Optional: Check for truncation
    if (written < 0) {
        // Handle encoding error if necessary, for now, clear the buffer.
        dest[0] = '\0';
    } else if ((size_t)written >= dest_size) {
        // This block is for information only. The string is already truncated safely.
        // printf("Warning: Input was truncated.\n");
    }
}

void run_test_case(int case_num, const char* input) {
    char processed_buffer[BUFFER_SIZE];
    
    // Always initialize buffers
    memset(processed_buffer, 0, sizeof(processed_buffer));

    printf("\nTest Case %d:\n", case_num);
    printf("Original:  \"%s\"\n", input);
    
    processString(processed_buffer, sizeof(processed_buffer), input);
    
    printf("Processed: \"%s\"\n", processed_buffer);
}

int main() {
    // --- Test Cases ---
    const char* testCases[] = {
        "Hello, World!",
        "",
        "This is a slightly longer string to test processing.",
        "A string with special characters: !@#$%^&*()_+",
        // This string is longer than the buffer to test truncation
        "This is a very long string designed to be much larger than the "
        "256-byte buffer to demonstrate how snprintf safely truncates the "
        "input without causing a buffer overflow. The output should stop "
        "before this sentence finishes, and the program should not crash."
    };
    int num_test_cases = sizeof(testCases) / sizeof(testCases[0]);

    printf("--- Running Test Cases ---\n");
    for (int i = 0; i < num_test_cases; ++i) {
        run_test_case(i + 1, testCases[i]);
    }

    // Example with user input
    printf("\n--- User Input Test ---\n");
    printf("Enter a string to process (max %d chars): ", BUFFER_SIZE - 1);
    
    char input_buffer[BUFFER_SIZE];
    char processed_user_buffer[BUFFER_SIZE];
    
    // Use fgets to safely read user input. It prevents buffer overflows
    // by reading at most sizeof(input_buffer) - 1 characters.
    if (fgets(input_buffer, sizeof(input_buffer), stdin)) {
        // Remove trailing newline character if present
        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        processString(processed_user_buffer, sizeof(processed_user_buffer), input_buffer);
        printf("Processed user input: \"%s\"\n", processed_user_buffer);
    } else {
        printf("Failed to read input.\n");
    }

    return 0;
}