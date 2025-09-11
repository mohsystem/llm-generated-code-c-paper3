#include <stdio.h>

int find(int integers[], int length) {
    int odd = 0, even = 0, oddCount = 0, evenCount = 0;
    for (int i = 0; i < length; i++) {
        if (integers[i] % 2 == 0) {
            even += integers[i];
            evenCount++;
        } else {
            odd += integers[i];
            oddCount++;
        }
    }
    return oddCount > evenCount ? even : odd;
}

int main() {
    int v1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int v2[] = {160, 3, 1719, 19, 11, 13, -21};
    printf("%d\n", find(v1, sizeof(v1)/sizeof(v1[0])));  // 11
    printf("%d\n", find(v2, sizeof(v2)/sizeof(v2[0])));  // 160
    return 0;
}