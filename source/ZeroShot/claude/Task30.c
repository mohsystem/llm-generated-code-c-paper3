
#include <stdio.h>
#include <string.h>

char* longest(const char* s1, const char* s2) {
    static char result[27];  // static to return local array
    int seen[26] = {0};
    int idx = 0;
    
    // Mark characters present in s1
    for(int i = 0; s1[i]; i++) {
        seen[s1[i] - 'a'] = 1;
    }
    
    // Mark characters present in s2
    for(int i = 0; s2[i]; i++) {
        seen[s2[i] - 'a'] = 1;
    }
    
    // Build result string
    for(int i = 0; i < 26; i++) {
        if(seen[i]) {
            result[idx++] = i + 'a';
        }
    }
    result[idx] = '\\0';
    
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
