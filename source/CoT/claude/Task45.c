
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_INPUT 256

char* processInput(const char* input, char* result) {
    // Check for null or empty input
    if (input == NULL || strlen(input) == 0) {
        strcpy(result, "Error: Input cannot be null or empty");
        return result;
    }
    
    // Check if input is only whitespace
    int hasNonSpace = 0;
    for(int i = 0; input[i]; i++) {
        if (!isspace(input[i])) {
            hasNonSpace = 1;
            break;
        }
    }
    if (!hasNonSpace) {
        strcpy(result, "Error: Input cannot be empty");
        return result;
    }
    
    // Convert string to number
    char* endptr;
    long num = strtol(input, &endptr, 10);
    
    // Check if conversion was successful
    if (*endptr != '\\0' && !isspace(*endptr)) {
        strcpy(result, "Error: Input must be a valid integer");
        return result;
    }
    
    // Check range
    if (num < 0) {
        strcpy(result, "Error: Number cannot be negative");
        return result;
    }
    if (num > INT_MAX) {
        strcpy(result, "Error: Input number too large");
        return result;
    }
    
    // Calculate square and cube
    long long square = (long long)num * num;
    long long cube = square * num;
    
    if (square > INT_MAX || cube > INT_MAX) {
        strcpy(result, "Error: Result too large");
        return result;
    }
    
    sprintf(result, "Square: %lld, Cube: %lld", square, cube);
    return result;
}

int main() {
    const char* inputs[] = {"10", "-5", "abc", "", "999999"};
    char result[MAX_INPUT];
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", inputs[i]);
        printf("Result: %s\\n\\n", processInput(inputs[i], result));
    }
    
    return 0;
}
