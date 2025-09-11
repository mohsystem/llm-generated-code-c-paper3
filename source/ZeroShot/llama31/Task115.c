#include <stdio.h>

struct Task115 {
    unsigned int bit0 : 1;
    unsigned int bit1to3 : 3;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6to7 : 2;
};

int main() {
    struct Task115 task;
    task.bit0 = 1;
    task.bit1to3 = 5;
    task.bit4 = 1;
    task.bit5 = 0;
    task.bit6to7 = 3;

    // Printing the values (note: direct bit field access is not possible in C)
    printf("bit0: %d\n", task.bit0);
    printf("bit1to3: %d\n", task.bit1to3);
    printf("bit4: %d\n", task.bit4);
    printf("bit5: %d\n", task.bit5);
    printf("bit6to7: %d\n", task.bit6to7);

    return 0;
}