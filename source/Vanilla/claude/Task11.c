
#include <stdio.h>

int nbYear(int p0, double percent, int aug, int p) {
    int years = 0;
    int population = p0;
    percent = percent / 100;
    
    while (population < p) {
        population = population + (int)(population * percent) + aug;
        years++;
    }
    return years;
}

int main() {
    // Test cases
    printf("%d\\n", nbYear(1500, 5, 100, 5000)); // 15
    printf("%d\\n", nbYear(1500000, 2.5, 10000, 2000000)); // 10
    printf("%d\\n", nbYear(1000, 2, 50, 1200)); // 3
    printf("%d\\n", nbYear(1500, 0.25, 1000, 2000)); // 1
    printf("%d\\n", nbYear(2000, 1.5, 10, 2100)); // 3
    return 0;
}
