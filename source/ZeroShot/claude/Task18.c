
#include <stdio.h>

int binary_array_to_number(int* binary, int length) {
    int result = 0;
    for(int i = 0; i < length; i++) {
        result = result * 2 + binary[i];
    }
    return result;
}

int main() {
    int testCases[][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Testing: [%d, %d, %d, %d] ==> %d\\n", 
               testCases[i][0], testCases[i][1], testCases[i][2], testCases[i][3],
               binary_array_to_number(testCases[i], 4));
    }
    return 0;
}
