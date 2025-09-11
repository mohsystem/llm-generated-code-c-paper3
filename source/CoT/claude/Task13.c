
#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(const char *walk, int length) {
    if (length != 10) return false;
    
    int ns = 0, ew = 0;
    for (int i = 0; i < length; i++) {
        switch (walk[i]) {
            case 'n': ns++; break;
            case 's': ns--; break;
            case 'e': ew++; break;
            case 'w': ew--; break;
        }
    }
    return ns == 0 && ew == 0;
}

int main() {
    // Test cases
    char test1[] = {'n','s','n','s','n','s','n','s','n','s'};
    char test2[] = {'w','e','w','e','w','e','w','e','w','e'};
    char test3[] = {'w'};
    char test4[] = {'n','n','n','s','n','s','n','s','n','s'};
    char test5[] = {'n','s','e','w','n','s','e','w','n','s'};
    
    printf("%d\\n", isValidWalk(test1, 10)); // 1
    printf("%d\\n", isValidWalk(test2, 10)); // 1
    printf("%d\\n", isValidWalk(test3, 1));  // 0
    printf("%d\\n", isValidWalk(test4, 10)); // 0
    printf("%d\\n", isValidWalk(test5, 10)); // 1
    
    return 0;
}
