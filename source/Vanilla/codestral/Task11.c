#include <stdio.h>

int nbYear(int p0, double percent, int aug, int p) {
    int years = 0;
    while (p0 < p) {
        p0 += p0 * percent / 100 + aug;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", nbYear(1500, 5, 100, 5000));  // Output: 15
    printf("%d\n", nbYear(1500000, 2.5, 10000, 2000000));  // Output: 10
    return 0;
}