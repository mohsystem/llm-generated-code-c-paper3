
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int get_digit_count(int number) {
    int count = 0;
    while (number > 0) {
        count++;
        number /= 10;
    }
    return count;
}

bool is_narcissistic(int number) {
    int len = get_digit_count(number);
    int sum = 0;
    int temp = number;
    
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, len);
        temp /= 10;
    }
    
    return sum == number;
}

int main() {
    printf("%d\\n", is_narcissistic(153));  // 1
    printf("%d\\n", is_narcissistic(1652)); // 0
    printf("%d\\n", is_narcissistic(370));  // 1
    printf("%d\\n", is_narcissistic(407));  // 1
    printf("%d\\n", is_narcissistic(1634)); // 1
    return 0;
}
