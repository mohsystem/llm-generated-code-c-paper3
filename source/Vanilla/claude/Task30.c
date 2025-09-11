
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longest(const char* s1, const char* s2) {
    int chars[26] = {0};
    int i;
    char* result = (char*)malloc(27); // 26 letters + null terminator
    int pos = 0;
    
    // Mark presence of characters
    for(i = 0; s1[i]; i++) chars[s1[i] - 'a'] = 1;
    for(i = 0; s2[i]; i++) chars[s2[i] - 'a'] = 1;
    
    // Create result string
    for(i = 0; i < 26; i++) {
        if(chars[i]) result[pos++] = i + 'a';
    }
    result[pos] = '\\0';
    
    return result;
}

int main() {
    printf("%s\\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"));
    printf("%s\\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"));
    printf("%s\\n", longest("aretheyhere", "yestheyarehere"));
    printf("%s\\n", longest("loopingisfunbutdangerous", "lessdangerousthancoding"));
    printf("%s\\n", longest("inmanylanguages", "theresapairoffunctions"));
    return 0;
}
