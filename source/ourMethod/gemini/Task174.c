#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to reverse a string
char* reverse_string(const char* str) {
    int n = strlen(str);
    char* reversed = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        reversed[i] = str[n - 1 - i];
    }
    reversed[n] = '\0';
    return reversed;
}

char* shortestPalindrome(const char* s) {
    int n = strlen(s);
    char* reversed_s = reverse_string(s);
    for (int i = 0; i < n; i++) {
        if (strncmp(s, reversed_s + i, n - i) == 0) {
            char* result = (char*)malloc((2 * i + n + 1) * sizeof(char));
            strncpy(result, reversed_s, i);
            strncpy(result + i, s, n);
            result[2*i + n] = '\0';
            free(reversed_s);
            return result;
        }
    }
    
    char *result = (char*) malloc((n+1) * sizeof(char));
    strcpy(result, s);

    free(reversed_s);
    return result;

}

int main() {
    char* testCase1 = "aacecaaa";
    char* expected1 = "aaacecaaa";
    char* result1 = shortestPalindrome(testCase1);
    printf("Test Case 1: %s\n", (strcmp(result1, expected1) == 0 ? "Passed" : "Failed"));
    free(result1);

    char* testCase2 = "abcd";
    char* expected2 = "dcbabcd";
    char* result2 = shortestPalindrome(testCase2);
    printf("Test Case 2: %s\n", (strcmp(result2, expected2) == 0 ? "Passed" : "Failed"));
    free(result2);

    char* testCase3 = "racecar";
    char* expected3 = "racecar";
    char* result3 = shortestPalindrome(testCase3);
    printf("Test Case 3: %s\n", (strcmp(result3, expected3) == 0 ? "Passed" : "Failed"));
    free(result3);


    char* testCase4 = "";
    char* expected4 = "";
    char* result4 = shortestPalindrome(testCase4);
    printf("Test Case 4: %s\n", (strcmp(result4, expected4) == 0 ? "Passed" : "Failed"));
    free(result4);

    char* testCase5 = "a";
    char* expected5 = "a";
    char* result5 = shortestPalindrome(testCase5);
    printf("Test Case 5: %s\n", (strcmp(result5, expected5) == 0 ? "Passed" : "Failed"));
    free(result5);

    return 0;
}