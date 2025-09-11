#include <stdio.h>
#include <string.h>

bool checkFlush(const char* table[5], const char* hand[2]) {
    int suitCounts[4] = {0};

    // Define suits
    const char* suits[4] = {"S", "H", "D", "C"};

    // Count suits on the table
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(table[i], suits[j])) {
                suitCounts[j]++;
                break;
            }
        }
    }

    // Count suits in the hand
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(hand[i], suits[j])) {
                suitCounts[j]++;
                break;
            }
        }
    }

    // Check if any suit has at least 5 cards
    for (int i = 0; i < 4; i++) {
        if (suitCounts[i] >= 5) {
            return true;
        }
    }

    return false;
}

int main() {
    // Test cases
    const char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1)); // true

    const char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2)); // true

    const char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3)); // false

    return 0;
}