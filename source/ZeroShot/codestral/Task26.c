#include <stdio.h>

int findIt(int A[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= A[i];
    }
    return result;
}

int main() {
    int A1[] = {7};
    int A2[] = {0};
    int A3[] = {1,1,2};
    int A4[] = {0,1,0,1,0};
    int A5[] = {1,2,2,3,3,3,4,3,3,3,2,2,1};

    printf("%d\n", findIt(A1, 1));
    printf("%d\n", findIt(A2, 1));
    printf("%d\n", findIt(A3, 3));
    printf("%d\n", findIt(A4, 5));
    printf("%d\n", findIt(A5, 13));

    return 0;
}