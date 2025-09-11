#include <stdio.h>
#include <math.h>

int nbYear(int p0, double percent, int aug, int p) {
    int years = 0;
    double currentPopulation = p0;
    percent = percent / 100;

    while (currentPopulation < p) {
        currentPopulation = floor(currentPopulation + currentPopulation * percent + aug);
        years++;
    }

    return years;
}

int main() {
    printf("%d\n", nbYear(1500, 5, 100, 5000)); // Output: 15
    printf("%d\n", nbYear(1500000, 2.5, 10000, 2000000)); // Output: 10
    return 0;
}