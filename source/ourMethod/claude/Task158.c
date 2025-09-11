
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

bool is_input_safe(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return false;
    }
    
    // Check each character is alphanumeric or allowed punctuation
    for (size_t i = 0; input[i] != '\\0'; i++) {
        if (!isalnum(input[i]) && 
            input[i] != '.' && 
            input[i] != '_' && 
            input[i] != '-' && 
            input[i] != ' ') {
            return false;
        }
    }
    return true;
}

char* execute_command(const char* input) {
    static char output[MAX_OUTPUT_LENGTH];
    output[0] = '\\0';
    
    if (!is_input_safe(input)) {
        strncpy(output, "Invalid input: Contains unsafe characters", MAX_OUTPUT_LENGTH - 1);
        return output;
    }
    
    // Create safe command
    char command[MAX_COMMAND_LENGTH];
    #ifdef _WIN32
        snprintf(command, sizeof(command), "dir %s", input);
    #else
        snprintf(command, sizeof(command), "ls %s", input);
    #endif
    
    // Execute command and capture output
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        strncpy(output, "Error executing command", MAX_OUTPUT_LENGTH - 1);
        return output;
    }
    
    char buffer[128];
    size_t output_len = 0;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t remaining = MAX_OUTPUT_LENGTH - output_len - 1;
        if (remaining == 0) break;
        
        size_t len = strlen(buffer);
        if (len > remaining) {
            len = remaining;
        }
        
        strncat(output + output_len, buffer, len);
        output_len += len;
    }
    
    int status = pclose(pipe);
    snprintf(output + output_len, MAX_OUTPUT_LENGTH - output_len, 
             "\\nExit Code: %d", status);
    
    return output;
}

int main() {
    const char* test_inputs[] = {
        "test.txt",
        "documents",
        "../dangerous",
        "file; rm -rf /",
        ""
    };
    
    for (int i = 0; i < 5; i++) {
        printf("\\nTest input: %s\\n", test_inputs[i]);
        printf("Result: %s\\n", execute_command(test_inputs[i]));
    }
    
    return 0;
}
