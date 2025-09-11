
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isConcat(const char* str, int len) {
    if(len % 2 != 0) return false;
    
    int half = len/2;
    for(int i = 0; i < half; i++) {
        if(str[i] != str[i + half]) return false;
    }
    return true;
}

int distinctSubstrings(const char* text) {
    int n = strlen(text);
    int count = 0;
    bool seen[2000][2000] = {false};
    
    for(int len = 2; len <= n; len += 2) {
        for(int i = 0; i <= n - len; i++) {
            if(!seen[i][len]) {
                char substr[2001];
                strncpy(substr, text + i, len);
                substr[len] = '\\0';
                
                if(isConcat(substr, len)) {
                    count++;
                    for(int j = i; j <= n - len; j++) {
                        bool match = true;
                        for(int k = 0; k < len; k++) {
                            if(text[j + k] != substr[k]) {
                                match = false;
                                break;
                            }
                        }
                        if(match) seen[j][len] = true;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    // Test cases
    printf("%d\\n", distinctSubstrings("abcabcabc")); // 3
    printf("%d\\n", distinctSubstrings("leetcodeleetcode")); // 2
    printf("%d\\n", distinctSubstrings("aa")); // 1
    printf("%d\\n", distinctSubstrings("abcd")); // 0
    printf("%d\\n", distinctSubstrings("aabaabaa")); // 4
    return 0;
}
