#include <stdio.h>
#include <string.h>

bool checkFlush(const char* table[5], const char* hand[2]) {
    int suitCounts[4] = {0, 0, 0, 0};
    char* suits[4] = {"S", "H", "D", "C"};

    // Count suits from table
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(table[i], suits[j])) {
                suitCounts[j]++;
                break;
            }
        }
    }

    // Count suits from hand
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
    const char* testTables[][5] = {
        {"A_S", "J_H", "7_D", "8_D", "10_D"},
        {"10_S", "7_S", "9_H", "4_S", "3_S"},
        {"3_S", "10_H", "10_D", "10_C", "10_S"},
        {"K_S", "Q_S", "J_S", "10_S", "9_S"},
        {"A_H", "K_H", "Q_H", "J_H", "10_H"}
    };

    const char* testHands[][2] = {
        {"J_D", "3_D"},
        {"K_S", "Q_S"},
        {"3_S", "4_D"},
        {"8_S", "7_S"},
        {"9_H", "8_H"}
    };

    for (int i = 0; i < 5; i++) {
        printf("Table: ");
        for (int j = 0; j < 5; j++) {
            printf("%s ", testTables[i][j]);
        }
        printf(", Hand: ");
        for (int j = 0; j < 2; j++) {
            printf("%s ", testHands[i][j]);
        }
        printf(" -> %s\n", checkFlush(testTables[i], testHands[i]) ? "true" : "false");
    }

    return 0;
}