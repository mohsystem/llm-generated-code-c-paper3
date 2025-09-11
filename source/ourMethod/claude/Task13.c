
#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(const char *walk, size_t length) {
    // Check if walk length is exactly 10 minutes
    if (length != 10) {
        return false;
    }
    
    // Track position relative to start
    int vertical = 0;    // north-south position
    int horizontal = 0;  // east-west position
    
    // Process each direction
    for (size_t i = 0; i < length; i++) {
        switch (walk[i]) {
            case 'n': vertical++; break;
            case 's': vertical--; break;
            case 'e': horizontal++; break;
            case 'w': horizontal--; break;
        }
    }
    
    // Return true if back at start position
    return vertical == 0 && horizontal == 0;
}

int main() {
    // Test cases
    char test1[] = {'n','s','n','s','n','s','n','s','n','s'};
    char test2[] = {'w','e','w','e','w','e','w','e','w','e'};
    char test3[] = {'n','n','n','s','n','s','n','s','n','s'};
    char test4[] = {'n','s','e','w','n','s','e','w','n','s'};
    char test5[] = {'n','s','n','s','n','s'};
    
    printf("%d\\n", isValidWalk(test1, 10)); // 1 (true)
    printf("%d\\n", isValidWalk(test2, 10)); // 1 (true)
    printf("%d\\n", isValidWalk(test3, 10)); // 0 (false)
    printf("%d\\n", isValidWalk(test4, 10)); // 1 (true)
    printf("%d\\n", isValidWalk(test5, 6));  // 0 (false)
    
    return 0;
}
