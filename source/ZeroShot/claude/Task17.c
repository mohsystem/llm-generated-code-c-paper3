
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void toJadenCase(char* str) {
    if(!str || !*str) return;
    
    bool capitalizeNext = true;
    
    for(int i = 0; str[i] != '\\0'; i++) {
        if(isspace(str[i])) {
            capitalizeNext = true;
        }
        else if(capitalizeNext) {
            str[i] = toupper(str[i]);
            capitalizeNext = false;
        }
    }
}

int main() {
    char tests[][100] = {
        "How can mirrors be real if our eyes aren't real",
        "School is the tool to brainwash the youth",
        "if everybody in the world dropped out of school we would have a much more intelligent society",
        "Most trees are blue",
        "All the rules in this world were made by someone no smarter than you"
    };
    
    for(int i = 0; i < 5; i++) {
        char test[100];
        strcpy(test, tests[i]);
        printf("Original: %s\\n", test);
        toJadenCase(test);
        printf("Jaden-Cased: %s\\n\\n", test);
    }
    
    return 0;
}
