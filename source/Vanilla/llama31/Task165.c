#include <stdio.h>
#include <string.h>

bool checkFlush(const char* tableCards[5], const char* handCards[2]) {
    const char* suits[] = {"S", "H", "D", "C"};
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (int j = 0; j < 5; j++) {
            if (strstr(tableCards[j], suits[i])) {
                count++;
            }
        }
        for (int j = 0; j < 2; j++) {
            if (strstr(handCards[j], suits[i])) {
                count++;
            }
        }
        if (count >= 5) {
            return true;
        }
    }
    return false;
}

int main() {
    const char* tableCards1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* handCards1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(tableCards1, handCards1)); // 1

    const char* tableCards2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* handCards2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(tableCards2, handCards2)); // 1

    const char* tableCards3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* handCards3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(tableCards3, handCards3)); // 0

    const char* tableCards4[] = {"A_H", "K_H", "Q_H", "J_H", "10_H"};
    const char* handCards4[] = {"9_H", "8_H"};
    printf("%d\n", checkFlush(tableCards4, handCards4)); // 1

    const char* tableCards5[] = {"2_C", "4_C", "6_C", "8_C", "10_C"};
    const char* handCards5[] = {"3_C", "5_C"};
    printf("%d\n", checkFlush(tableCards5, handCards5)); // 1

    return 0;
}