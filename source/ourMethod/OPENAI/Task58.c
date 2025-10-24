#include <stdio.h>
#include <stdbool.h>

bool XO(const char *s) {
    if (s == NULL) {
        return false; // fail closed on invalid input
    }
    int xCount = 0;
    int oCount = 0;
    for (const char *p = s; *p != '\0'; ++p) {
        char c = *p;
        if (c == 'x' || c == 'X') {
            xCount++;
        } else if (c == 'o' || c == 'O') {
            oCount++;
        }
    }
    return xCount == oCount;
}

static const char* bool_str(bool v) {
    return v ? "true" : "false";
}

int main(void) {
    const char *tests[5] = {"ooxx", "xooxx", "ooxXm", "zpzpzpp", "zzoo"};
    bool expected[5] = {true, false, true, true, false};
    for (int i = 0; i < 5; ++i) {
        bool res = XO(tests[i]);
        printf("XO(\"%s\") => %s (expected %s)\n", tests[i], bool_str(res), bool_str(expected[i]));
    }
    return 0;
}