#include <stdio.h>

void createPhoneNumber(int numbers[10], char *result) {
    sprintf(result, "(%d%d%d) %d%d%d-%d%d%d%d", 
            numbers[0], numbers[1], numbers[2], 
            numbers[3], numbers[4], numbers[5], 
            numbers[6], numbers[7], numbers[8], numbers[9]);
}

int main() {
    char result[15];
    
    int numbers1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    createPhoneNumber(numbers1, result);
    printf("%s\n", result);
    
    int numbers2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    createPhoneNumber(numbers2, result);
    printf("%s\n", result);
    
    int numbers3[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    createPhoneNumber(numbers3, result);
    printf("%s\n", result);
    
    int numbers4[10] = {2, 4, 6, 8, 0, 1, 3, 5, 7, 9};
    createPhoneNumber(numbers4, result);
    printf("%s\n", result);
    
    int numbers5[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    createPhoneNumber(numbers5, result);
    printf("%s\n", result);

    return 0;
}