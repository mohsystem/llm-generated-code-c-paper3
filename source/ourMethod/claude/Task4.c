
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isIsogram(const char *str) {
    if (str == NULL || *str == '\\0') {
        return true;
    }
    
    // Create boolean array to track seen characters
    bool seen[26] = {false};
    
    // Check each character
    for (int i = 0; str[i] != '\\0'; i++) {
        // Skip non-letter characters
        if (!isalpha(str[i])) {
            continue;
        }
        
        // Convert to lowercase and get array index
        int index = tolower(str[i]) - 'a';
        
        // If character already seen, not an isogram
        if (seen[index]) {
            return false;
        }
        
        // Mark character as seen
        seen[index] = true;
    }
    
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", isIsogram("Dermatoglyphics")); // 1 (true)
    printf("%d\\n", isIsogram("aba")); // 0 (false)
    printf("%d\\n", isIsogram("moOse")); // 0 (false)
    printf("%d\\n", isIsogram("")); // 1 (true)
    printf("%d\\n", isIsogram("isogram")); // 1 (true)
    return 0;
}
