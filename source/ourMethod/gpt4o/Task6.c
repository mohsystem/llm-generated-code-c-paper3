#include <stdio.h>
#include <stdlib.h>

double findUniq(double arr[], int size) {
    double a = arr[0];
    if (a != arr[1] && a != arr[2]) {
        return a;
    }
    for (int i = 0; i < size; ++i) {
        if (arr[i] != a) {
            return arr[i];
        }
    }
    fprintf(stderr, "No unique number found\n");
    exit(EXIT_FAILURE);
}

int main() {
    printf("%f\n", findUniq((double[]){1, 1, 1, 2, 1, 1}, 6)); // 2
    printf("%f\n", findUniq((double[]){0, 0, 0.55, 0, 0}, 5)); // 0.55
    printf("%f\n", findUniq((double[]){3, 3, 3, 3, 4}, 5)); // 4
    printf("%f\n", findUniq((double[]){2, 2, 1, 2, 2}, 5)); // 1
    printf("%f\n", findUniq((double[]){5, 5, 5, 5, 6}, 5)); // 6
    return 0;
}