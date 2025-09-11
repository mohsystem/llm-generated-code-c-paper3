#include <stdio.h>
#include <stdbool.h>

bool isValidWalk(char walk[], int n) {
    if (n != 10) return false;
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
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
    char walk1[] = {'n','s','n','s','n','s','n','s','n','s'};
    char walk2[] = {'w','e','w','e','w','e','w','e','w','e','w','e'};
    char walk3[] = {'w'};
    char walk4[] = {'n','n','n','n','n','n','n','n','n','n'};
    char walk5[] = {'n','s','e','w','n','s','e','w','n','s'};
    printf("%d\n", isValidWalk(walk1, 10)); // 1 (true)
    printf("%d\n", isValidWalk(walk2, 12)); // 0 (false)
    printf("%d\n", isValidWalk(walk3, 1)); // 0 (false)
    printf("%d\n", isValidWalk(walk4, 10)); // 0 (false)
    printf("%d\n", isValidWalk(walk5, 10)); // 1 (true)
    return 0;
}