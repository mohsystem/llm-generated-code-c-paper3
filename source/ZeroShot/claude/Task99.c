
#include <stdio.h>
#include <regex.h>
#include <string.h>

int matchLine(const char* line) {
    if (line == NULL) return 0;
    
    regex_t regex;
    int ret;
    
    // Compile regular expression
    ret = regcomp(&regex, "^[0-9].*\\\\.$", REG_EXTENDED);
    if (ret) return 0;
    
    // Execute regular expression
    ret = regexec(&regex, line, 0, NULL, 0);
    regfree(&regex);
    
    return (ret == 0);
}

int main() {
    // Test cases
    const char* testLines[] = {
        "123 test line.",
        "456 another test.",
        "Not starting with number.",
        "789 no dot",
        "0 simple line."
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Line: %s\\n", testLines[i]);
        printf("Matches: %d\\n", matchLine(testLines[i]));
    }
    
    return 0;
}
