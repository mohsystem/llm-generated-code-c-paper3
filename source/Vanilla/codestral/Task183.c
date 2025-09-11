#include<stdio.h>
#include<string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
int maxProduct(char* num, int k) {
    int n = strlen(num);
    if (n < k) {
        return -1;
    }
    int maxProd = 0;
    for (int i = 0; i <= n - k; i++) {
        int prod = 1;
        for (int j = i; j < i + k; j++) {
            prod *= num[j] - '0';
        }
        maxProd = max(maxProd, prod);
    }
    return maxProd;
}
int main() {
    printf("%d", maxProduct("63915", 3)); // Output: 162
    return 0;
}