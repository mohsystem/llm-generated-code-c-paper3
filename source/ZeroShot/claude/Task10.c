
#include <stdio.h>

int getSum(int a, int b) {
    if (a == b) return a;
    
    int start = (a < b) ? a : b;
    int end = (a > b) ? a : b;
    
    return (end - start + 1) * (start + end) / 2;
}

int main() {
    printf("%d\\n", getSum(1, 0));   // 1
    printf("%d\\n", getSum(1, 2));   // 3
    printf("%d\\n", getSum(0, 1));   // 1
    printf("%d\\n", getSum(1, 1));   // 1
    printf("%d\\n", getSum(-1, 2));  // 2
    return 0;
}
