
#include <stdio.h>
#include <regex.h>
#include <string.h>

int matchLine(const char* line) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[0-9].*\\\\.$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\\n");
        return 0;
    }

    // Execute regular expression
    reti = regexec(&regex, line, 0, NULL, 0);
    regfree(&regex);
    
    return (reti == 0);
}

int main() {
    // Test cases
    const char* tests[] = {
        "123 abc.",
        "456 def test.",
        "abc 123.",
        "789.",
        "1 this is a test."
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Line: %s\\n", tests[i]);
        printf("Matches: %s\\n", matchLine(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
