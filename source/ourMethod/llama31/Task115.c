#include <stdio.h>

struct Task115 {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int flag3 : 1;
};

int main() {
    struct Task115 task;
    task.flag1 = 1;
    task.flag2 = 0;
    task.flag3 = 1;

    printf("Flag1: %d\n", task.flag1);
    printf("Flag2: %d\n", task.flag2);
    printf("Flag3: %d\n", task.flag3);

    return 0;
}