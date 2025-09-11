
#include <stdio.h>
#include <string.h>

void createPhoneNumber(const int arr[10], char *result) {
    if (arr == NULL || result == NULL) {
        if (result) *result = '\\0';
        return;
    }
    
    for (int i = 0; i < 10; i++) {
        if (arr[i] < 0 || arr[i] > 9) {
            *result = '\\0';
            return;
        }
    }
    
    sprintf(result, "(%d%d%d) %d%d%d-%d%d%d%d",
            arr[0], arr[1], arr[2], arr[3], arr[4],
            arr[5], arr[6], arr[7], arr[8], arr[9]);
}

int main() {
    int testCases[][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {9, 9, 9, 8, 8, 8, 7, 7, 7, 6},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    char result[15];
    for (int i = 0; i < 5; i++) {
        createPhoneNumber(testCases[i], result);
        printf("%s\\n", result);
    }
    return 0;
}
