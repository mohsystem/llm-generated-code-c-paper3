#include <stdio.h>
#include <string.h>

int checkFlush(const char* tableCards[], int tableSize, const char* handCards[], int handSize) {
    int suitCount[256] = {0}; // ASCII suits S, H, D, C

    for (int i = 0; i < tableSize; i++) {
        char suit = tableCards[i][strlen(tableCards[i]) - 1];
        suitCount[(int)suit]++;
    }

    for (int i = 0; i < handSize; i++) {
        char suit = handCards[i][strlen(handCards[i]) - 1];
        suitCount[(int)suit]++;
    }

    for (int i = 0; i < 256; i++) {
        if (suitCount[i] >= 5) {
            return 1; // true
        }
    }
    return 0; // false
}

int main() {
    const char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, 5, hand1, 2)); // true

    const char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, 5, hand2, 2)); // true

    const char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, 5, hand3, 2)); // false

    const char* table4[] = {"2_H", "3_H", "4_H", "5_H", "9_D"};
    const char* hand4[] = {"6_H", "7_C"};
    printf("%d\n", checkFlush(table4, 5, hand4, 2)); // true

    const char* table5[] = {"2_D", "3_D", "4_H", "5_C", "9_D"};
    const char* hand5[] = {"6_D", "7_D"};
    printf("%d\n", checkFlush(table5, 5, hand5, 2)); // true

    return 0;
}