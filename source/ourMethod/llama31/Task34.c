#include <stdio.h>
#include <string.h>
#include <math.h>

bool isNarcissistic(int number) {
    char numStr[100];
    sprintf(numStr, "%d", number);
    int numDigits = strlen(numStr);
    int sum = 0;
    for (int i = 0; i < numDigits; i++) {
        sum += (int) pow(numStr[i] - '0', numDigits);
    }
    return sum == number;
}

int main() {
    int testCases[] = {153, 407, 1634, 1652, 9474};
    for (int i = 0; i < 5; i++) {
        printf("%d is narcissistic: %s\n", testCases[i], isNarcissistic(testCases[i]) ? "true" : "false");
    }
    return 0;
}