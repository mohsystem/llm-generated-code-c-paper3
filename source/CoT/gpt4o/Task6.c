#include <stdio.h>

double findUniq(double arr[], int size) {
    double a = arr[0], b = arr[1], c = arr[2];
    if (a != b && a != c) return a;
    for (int i = 0; i < size; i++) {
        if (arr[i] != a) return arr[i];
    }
    return -1; // should never reach here
}

int main() {
    printf("%lf\n", findUniq((double[]){1, 1, 1, 2, 1, 1}, 6)); // => 2
    printf("%lf\n", findUniq((double[]){0, 0, 0.55, 0, 0}, 5)); // => 0.55
    printf("%lf\n", findUniq((double[]){3, 3, 2, 3, 3}, 5)); // => 2
    printf("%lf\n", findUniq((double[]){4, 4, 4, 4, 5}, 5)); // => 5
    printf("%lf\n", findUniq((double[]){6, 7, 6, 6, 6}, 5)); // => 7
    return 0;
}