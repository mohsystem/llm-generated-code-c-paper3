
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char* str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    if(len <= 1) return s;
    
    char* temp = (char*)malloc(2*len + 2);
    strcpy(temp, s);
    temp[len] = '#';
    for(int i = 0; i < len; i++) {
        temp[len+1+i] = s[len-1-i];
    }
    temp[2*len+1] = '\\0';
    
    int* lps = (int*)calloc(2*len+1, sizeof(int));
    int length = 0;
    int i = 1;
    
    while(i < 2*len+1) {
        if(temp[i] == temp[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if(length != 0) {
                length = lps[length-1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    char* result = (char*)malloc(2*len + 1);
    int matchLen = lps[2*len];
    int addLen = len - matchLen;
    
    for(i = 0; i < addLen; i++) {
        result[i] = s[len-1-i];
    }
    strcpy(result + addLen, s);
    
    free(temp);
    free(lps);
    return result;
}

int main() {
    printf("%s\\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\\n", shortestPalindrome("aaa")); // "aaa"
    printf("%s\\n", shortestPalindrome("aaaa")); // "aaaa"
    printf("%s\\n", shortestPalindrome("")); // ""
    return 0;
}
