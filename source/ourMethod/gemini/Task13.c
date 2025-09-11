#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidWalk(char* walk, int walkLength) {
    if (walkLength != 10) {
        return false;
    }

    int n_count = 0;
    int s_count = 0;
    int e_count = 0;
    int w_count = 0;


    for (int i = 0; i < walkLength; i++) {
        if (walk[i] == 'n') {
            n_count++;
        } else if (walk[i] == 's') {
            s_count++;
        } else if (walk[i] == 'e') {
            e_count++;
        } else if (walk[i] == 'w') {
            w_count++;
        }
    }

    return n_count == s_count && e_count == w_count;
}

int main() {
    char walk1[] = "nsnsnsnsns";
    printf("%s\n", isValidWalk(walk1, strlen(walk1)) ? "true" : "false"); // true

    char walk2[] = "wewewewewewe";
    printf("%s\n", isValidWalk(walk2, strlen(walk2)) ? "true" : "false"); // false

    char walk3[] = "w";
    printf("%s\n", isValidWalk(walk3, strlen(walk3)) ? "true" : "false"); // false

    char walk4[] = "nnnsnsnsns";
    printf("%s\n", isValidWalk(walk4, strlen(walk4)) ? "true" : "false"); // false

    char walk5[] = "ewnsnsewns";
    printf("%s\n", isValidWalk(walk5, strlen(walk5)) ? "true" : "false"); // true

    return 0;
}