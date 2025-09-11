
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

char* handle_input(const char* input) {
    static char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    if (input == NULL) {
        buffer[0] = '\\0';
        return buffer;
    }
    
    // Safely copy input to buffer with bounds checking
    size_t length = strlen(input);
    if (length >= BUFFER_SIZE) {
        length = BUFFER_SIZE - 1;
    }
    
    strncpy(buffer, input, length);
    buffer[length] = '\\0'; // Ensure null termination
    
    return buffer;
}

int main() {
    // Test cases
    const char* tests[] = {
        "Hello World",
        "This is a very long input that exceeds the buffer size limit and should be truncated safely",
        "",
        NULL,
        "Test123!@#"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "NULL");
        printf("Output: %s\\n\\n", handle_input(tests[i]));
    }
    
    return 0;
}
