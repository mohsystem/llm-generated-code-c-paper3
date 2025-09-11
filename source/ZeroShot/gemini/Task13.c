#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidWalk(char walk[], int size) {
    if (size != 10) {
        return false;
    }
    int x = 0, y = 0;
    for (int i = 0; i < size; i++) {
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
    printf("%d\n", isValidWalk(test1, sizeof(test1)/sizeof(test1[0]))); // 1 (true)
    char test2[] = {'w','e','w','e','w','e','w','e','w','e','w','e'};
    printf("%d\n", isValidWalk(test2, sizeof(test2)/sizeof(test2[0]))); // 0 (false)
    char test3[] = {'w'};
    printf("%d\n", isValidWalk(test3, sizeof(test3)/sizeof(test3[0]))); // 0 (false)
    char test4[] = {'n','n','n','s','n','s','n','s','n','s'};
    printf("%d\n", isValidWalk(test4, sizeof(test4)/sizeof(test4[0]))); // 0 (false)
    char test5[] = {'n','s','e','w','n','s','e','w','n','s'};
    printf("%d\n", isValidWalk(test5, sizeof(test5)/sizeof(test5[0]))); // 1 (true)

    return 0;
}