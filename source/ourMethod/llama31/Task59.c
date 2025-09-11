#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* accum(char* str) {
    static char result[1024]; // Buffer size assumption
    char* ptr = result;
    for (int i = 0; str[i]; ++i) {
        char c = str[i];
        // Ensure the character is a letter
        if (isalpha(c)) {
            // Capitalize the first letter and repeat it i+1 times
            *ptr++ = toupper(c);
            for (int j = 1; j <= i; ++j) {
                *ptr++ = tolower(c);
            }
            // Add a hyphen after each character except the last one
            if (str[i + 1]) {
                *ptr++ = '-';
            }
        } else {
            // Handle non-letter characters by skipping them
            continue;
        }
    }
    *ptr = '\0'; // Null terminate the string
    return result;
}

int main() {
    printf("%s\n", accum("abcd"));  // "A-Bb-Ccc-Dddd"
    printf("%s\n", accum("RqaEzty"));  // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    printf("%s\n", accum("cwAt"));  // "C-Ww-Aaa-Tttt"
    return 0;
}