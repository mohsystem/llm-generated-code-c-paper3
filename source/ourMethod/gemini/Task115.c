#include <stdio.h>

struct BitFields {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int value : 6;
};

int main() {
    struct BitFields bf1;
    bf1.flag1 = 1;
    bf1.flag2 = 0;
    bf1.value = 32;
    printf("bf1: flag1=%d, flag2=%d, value=%d\n", bf1.flag1, bf1.flag2, bf1.value);

    struct BitFields bf2;
    bf2.flag1 = 0;
    bf2.flag2 = 1;
    bf2.value = 15;
    printf("bf2: flag1=%d, flag2=%d, value=%d\n", bf2.flag1, bf2.flag2, bf2.value);

    struct BitFields bf3;
    bf3.flag1 = 1;
    bf3.flag2 = 1;
    bf3.value = 63;
    printf("bf3: flag1=%d, flag2=%d, value=%d\n", bf3.flag1, bf3.flag2, bf3.value);

    struct BitFields bf4;
    bf4.flag1 = 0;
    bf4.flag2 = 0;
    bf4.value = 0;
    printf("bf4: flag1=%d, flag2=%d, value=%d\n", bf4.flag1, bf4.flag2, bf4.value);

    struct BitFields bf5;
    bf5.flag1 = 1;
    bf5.flag2 = 0;
    bf5.value = 55;
    printf("bf5: flag1=%d, flag2=%d, value=%d\n", bf5.flag1, bf5.flag2, bf5.value);

    return 0;
}