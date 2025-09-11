#include <stdio.h>

double findUniq(double arr[], int n) {
    double first = arr[0];
    double second = arr[1];
    if (first != second && first == arr[2]) {
        return second;
    } else {
        return first;
    }
}

int main() {
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {3, 3, 3, 4, 3, 3};
    double test4[] = {5, 5, 5, 5, 6};
    double test5[] = {7, 7, 7, 8, 7};

    printf("%f\n", findUniq(test1, 6)); // => 2
    printf("%f\n", findUniq(test2, 5)); // => 0.55
    printf("%f\n", findUniq(test3, 6)); // => 4
    printf("%f\n", findUniq(test4, 5)); // => 6
    printf("%f\n", findUniq(test5, 5)); // => 8

    return 0;
}