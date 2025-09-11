
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool XO(const char* str) {
    int x = 0, o = 0;
    
    for(int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if(c == 'x') x++;
        if(c == 'o') o++;
    }
    
    return x == o;
}

int main() {
    printf("%d\\n", XO("ooxx"));     // 1
    printf("%d\\n", XO("xooxx"));    // 0
    printf("%d\\n", XO("ooxXm"));    // 1
    printf("%d\\n", XO("zpzpzpp"));  // 1
    printf("%d\\n", XO("zzoo"));     // 0
    return 0;
}
