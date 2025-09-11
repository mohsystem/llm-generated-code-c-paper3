
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toJadenCase(char* phrase) {
    if (!phrase || !*phrase) return;
    
    int capitalizeNext = 1;
    for (int i = 0; phrase[i] != '\\0'; i++) {
        if (isspace(phrase[i])) {
            capitalizeNext = 1;
        } else if (capitalizeNext) {
            phrase[i] = toupper(phrase[i]);
            capitalizeNext = 0;
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
    
    for (int i = 0; i < 5; i++) {
        char buffer[100];
        strcpy(buffer, tests[i]);
        
        printf("Original: %s\\n", buffer);
        toJadenCase(buffer);
        printf("Jaden Case: %s\\n\\n", buffer);
    }
    
    return 0;
}
