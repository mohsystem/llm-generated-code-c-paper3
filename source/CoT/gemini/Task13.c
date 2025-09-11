#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidWalk(char walk[], int len) {
    if (len != 10) {
        return false;
    }

    int x = 0;
    int y = 0;

    for (int i = 0; i < len; i++) {
        switch (walk[i]) {
            case 'n':
                y++;
                break;
            case 's':
                y--;
                break;
            case 'e':
                x++;
                break;
            case 'w':
                x--;
                break;
        }
    }

    return x == 0 && y == 0;
}

int main() {
    char walk1[] = {'n', 's', 'n', 's', 'n', 's', 'n', 's', 'n', 's'};
    printf("%d\n", isValidWalk(walk1, sizeof(walk1))); // 1 (true)

    char walk2[] = {'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e'};
    printf("%d\n", isValidWalk(walk2, sizeof(walk2))); // 0 (false)

    char walk3[] = {'w'};
    printf("%d\n", isValidWalk(walk3, sizeof(walk3))); // 0 (false)


    char walk4[] = {'n', 'n', 'n', 's', 'n', 's', 'n', 's', 'n', 's'};
    printf("%d\n", isValidWalk(walk4, sizeof(walk4))); // 0 (false)

    char walk5[] = {'e', 'w', 'e', 'w', 'n', 's', 'n', 's', 'e', 'w'};
    printf("%d\n", isValidWalk(walk5, sizeof(walk5))); // 1 (true)

    return 0;
}