#include <stdbool.h>
#include <stdio.h>

bool isValidWalk(const char *walk, size_t length) {
    if (length != 10)
        return false;
    int x = 0, y = 0;
    for (size_t i = 0; i < length; i++) {
        char direction = walk[i];
        if (direction == 'n') y++;
        else if (direction == 's') y--;
        else if (direction == 'e') x++;
        else if (direction == 'w') x--;
    }
    return x == 0 && y == 0;
}

int main() {
    const char walk1[] = {'n','s','n','s','n','s','n','s','n','s'};
    printf("%s\n", isValidWalk(walk1, sizeof(walk1)) ? "true" : "false"); // true

    const char walk2[] = {'w','e','w','e','w','e','w','e','w','e','w','e'};
    printf("%s\n", isValidWalk(walk2, sizeof(walk2)) ? "true" : "false"); // false

    const char walk3[] = {'w'};
    printf("%s\n", isValidWalk(walk3, sizeof(walk3)) ? "true" : "false"); // false

    const char walk4[] = {'n','n','n','s','n','s','n','s','n','s'};
    printf("%s\n", isValidWalk(walk4, sizeof(walk4)) ? "true" : "false"); // false

    return 0;
}