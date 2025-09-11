#include <stdio.h>

int nbYear(int p0, double percent, int aug, int p) {
    int years = 0;
    double population = p0;
    while (population < p) {
        population += population * (percent / 100) + aug;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", nbYear(1500, 5, 100, 5000)); // Expected 15
    printf("%d\n", nbYear(1500000, 2.5, 10000, 2000000)); // Expected 10
    printf("%d\n", nbYear(1000, 2, 50, 1200)); // Expected 3
    printf("%d\n", nbYear(1000, 2, -50, 1200)); // Expected 5
    printf("%d\n", nbYear(1500, 5, 100, 1500)); // Expected 0
    return 0;
}