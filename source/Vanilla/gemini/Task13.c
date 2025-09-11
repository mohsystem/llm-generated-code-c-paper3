#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidWalk(char walk[], int len) {
    if (len != 10) {
        return false;
    }
    int x = 0, y = 0;
    for (int i = 0; i < len; i++) {
        switch (walk[i]) {
            case 'n': y++; break;
            case 's': y--; break;
            case 'e': x++; break;
            case 'w': x--; break;
        }
    }
    return x == 0 && y == 0;
}

int main() {
    char test1[] = {'n','s','n','s','n','s','n','s','n','s'};
    printf("%d\n", isValidWalk(test1, sizeof(test1))); // true (1)

    char test2[] = {'w','e','w','e','w','e','w','e','w','e','w','e'};
    printf("%d\n", isValidWalk(test2, sizeof(test2))); // false (0)

    char test3[] = {'w'};
    printf("%d\n", isValidWalk(test3, sizeof(test3))); // false (0)

    char test4[] = {'n','n','n','s','n','s','n','s','n','s'};
    printf("%d\n", isValidWalk(test4, sizeof(test4))); // false (0)
    
    char test5[] = {'e','w','e','w','n','s','n','s','e','w'};
    printf("%d\n", isValidWalk(test5, sizeof(test5))); // true (1)

    return 0;
}