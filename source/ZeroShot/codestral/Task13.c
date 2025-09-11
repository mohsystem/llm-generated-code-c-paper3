#include<stdio.h>
#include<stdbool.h>

bool isValidWalk(char walk[], int size) {
    if (size != 10) return false;
    int x = 0, y = 0;
    for (int i = 0; i < size; i++) {
        if (walk[i] == 'n') y++;
        else if (walk[i] == 's') y--;
        else if (walk[i] == 'e') x++;
        else if (walk[i] == 'w') x--;
    }
    return x == 0 && y == 0;
}

int main() {
    char walk1[] = {'n', 's', 'n', 's', 'n', 's', 'n', 's', 'n', 's'};
    char walk2[] = {'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e'};
    char walk3[] = {'n', 's', 'e', 'w', 'n', 's', 'e', 'w', 'n', 's'};
    char walk4[] = {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n'};
    char walk5[] = {'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n', 's', 's', 's', 's', 's'};

    printf("%d\n", isValidWalk(walk1, 10));  // 1
    printf("%d\n", isValidWalk(walk2, 12));  // 0
    printf("%d\n", isValidWalk(walk3, 10));  // 1
    printf("%d\n", isValidWalk(walk4, 10));  // 0
    printf("%d\n", isValidWalk(walk5, 14));  // 0

    return 0;
}