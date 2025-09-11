
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool XO(const char* str) {
    if (str == NULL) {
        return true;
    }
    
    int xCount = 0;
    int oCount = 0;
    
    for (int i = 0; str[i] != '\\0'; i++) {
        char c = tolower(str[i]);
        if (c == 'x') {
            xCount++;
        } else if (c == 'o') {
            oCount++;
        }
    }
    
    return xCount == oCount;
}

int main() {
    // Test cases
    printf("%s\\n", XO("ooxx") ? "true" : "false"); // true
    printf("%s\\n", XO("xooxx") ? "true" : "false"); // false
    printf("%s\\n", XO("ooxXm") ? "true" : "false"); // true
    printf("%s\\n", XO("zpzpzpp") ? "true" : "false"); // true
    printf("%s\\n", XO("zzoo") ? "true" : "false"); // false
    return 0;
}
