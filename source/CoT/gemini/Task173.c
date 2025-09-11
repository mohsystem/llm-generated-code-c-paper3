#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Note: C does not have a built-in hash set, making efficient substring
// searching more complex. This implementation uses a simpler approach
// suitable for smaller strings and may not be as performant as the
// other language versions for larger inputs.  For a more robust
// solution, consider implementing a custom hash table or using a
// specialized string searching algorithm.


// This C version provides a basic implementation but may not be as efficient
// as the Java, Python, and C++ versions due to the lack of a built-in hash set.

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int left = 1;
    int right = n - 1;
    char* result = "";
    int result_len = 0;


    while (left <= right) {
        int mid = left + (right - left) / 2;
        char* duplicate = findDuplicateSubstring(s, mid);
         if (duplicate != NULL) {
            if (strlen(duplicate) > result_len)
            {
                result = duplicate;
                result_len = strlen(duplicate);

            }
            
            left = mid + 1;

         }
          else {
                right = mid - 1;
            }
    }
    return result;
}

char* findDuplicateSubstring(char* s, int len) {
     int n = strlen(s);
 for (int i = 0; i <= n - len; i++) {
        for (int j = i + 1; j <= n - len; j++) {
            if (strncmp(s + i, s + j, len) == 0) {
              char* sub = (char*)malloc(sizeof(char) * (len+1));
              strncpy(sub, s+i, len);
              sub[len] = '\0';
                return sub;
            }
        }
    }
    return NULL;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // Output: ana
    printf("%s\n", longestDupSubstring("abcd"));   // Output: 
    printf("%s\n", longestDupSubstring("aa"));     // Output: a
    printf("%s\n", longestDupSubstring("abcabcbb")); // Output: abc
    printf("%s\n", longestDupSubstring("bbbbb"));  // Output: bbbb

    return 0;
}