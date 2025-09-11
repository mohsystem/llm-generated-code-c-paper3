
#include <stdio.h>
#include <math.h>

int countDigits(int num) {
    int count = 0;
    while(num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int isNarcissistic(int number) {
    int original = number;
    int power = countDigits(number);
    int sum = 0;
    
    while(number > 0) {
        int digit = number % 10;
        sum += pow(digit, power);
        number /= 10;
    }
    
    return sum == original;
}

int main() {
    printf("%d\\n", isNarcissistic(153));  // 1
    printf("%d\\n", isNarcissistic(1652)); // 0
    printf("%d\\n", isNarcissistic(370));  // 1
    printf("%d\\n", isNarcissistic(407));  // 1
    printf("%d\\n", isNarcissistic(1634)); // 1
    return 0;
}
