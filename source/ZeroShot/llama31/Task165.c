#include <stdio.h>
#include <string.h>

bool checkFlush(const char* table[5], const char* hand[2]) {
    int suitCount[4] = {0}; // 0: Spades, 1: Hearts, 2: Diamonds, 3: Clubs
    char* suits[] = {"S", "H", "D", "C"};

    // Count suits on the table
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(table[i], suits[j])) {
                suitCount[j]++;
                break;
            }
        }
    }

    // Count suits in the hand
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(hand[i], suits[j])) {
                suitCount[j]++;
                break;
            }
        }
    }

    // Check if any suit has at least 5 cards
    for (int count : suitCount) {
        if (count >= 5) {
            return true;
        }
    }

    return false;
}

int main() {
    const char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1)); // true

    const char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2)); // true

    const char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3)); // false

    const char* table4[] = {"K_H", "Q_H", "J_H", "10_H", "9_H"};
    const char* hand4[] = {"8_H", "7_H"};
    printf("%d\n", checkFlush(table4, hand4)); // true

    const char* table5[] = {"A_C", "K_C", "Q_C", "J_C", "10_C"};
    const char* hand5[] = {"9_C", "8_C"};
    printf("%d\n", checkFlush(table5, hand5)); // true

    return 0;
}