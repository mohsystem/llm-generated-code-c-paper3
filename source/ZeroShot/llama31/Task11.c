#include <stdio.h>

int nbYear(int p0, double percent, int aug, int p) {
    int years = 0;
    while (p0 < p) {
        p0 = p0 + (int)(p0 * (percent / 100)) + aug;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", nbYear(1000, 2, 50, 1200)); // 3
    printf("%d\n", nbYear(1500, 5, 100, 5000)); // 15
    printf("%d\n", nbYear(1500000, 2.5, 10000, 2000000)); // 10
    printf("%d\n", nbYear(100, 2, 50, 120)); // 3
    printf("%d\n", nbYear(50000, 2, 2000, 100000)); // 10
    return 0;
}