#include <stdio.h>

double findUniq(double arr[], int n) {
    double first = arr[0];
    double second = arr[1];
    if (first != second && first != arr[2]) {
        return first;
    } else if (second != arr[2]) {
        return second;
    } else {
        for (int i = 2; i < n; i++) {
            if (arr[i] != first) {
                return arr[i];
            }
        }
    }
    return 0; // This line should not be reached
}

int main() {
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {3, 3, 3, 4, 3, 3};
    double test4[] = {5, 5, 5, 6, 5, 5};
    double test5[] = {7, 7, 7.7, 7, 7};

    int n1 = sizeof(test1) / sizeof(test1[0]);
    int n2 = sizeof(test2) / sizeof(test2[0]);
    int n3 = sizeof(test3) / sizeof(test3[0]);
    int n4 = sizeof(test4) / sizeof(test4[0]);
    int n5 = sizeof(test5) / sizeof(test5[0]);

    printf("%f\n", findUniq(test1, n1));   // => 2
    printf("%f\n", findUniq(test2, n2));   // => 0.55
    printf("%f\n", findUniq(test3, n3));   // => 4
    printf("%f\n", findUniq(test4, n4));   // => 6
    printf("%f\n", findUniq(test5, n5));   // => 7.7

    return 0;
}