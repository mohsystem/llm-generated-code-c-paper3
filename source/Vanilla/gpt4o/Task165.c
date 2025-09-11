#include <stdio.h>
#include <string.h>

int checkFlush(char table[][5], char hand[][5], int tableSize, int handSize) {
    int suits[4] = {0}; // Indexes: 0 - Spades, 1 - Hearts, 2 - Diamonds, 3 - Clubs

    for (int i = 0; i < tableSize; i++) {
        switch (table[i][strlen(table[i]) - 1]) {
            case 'S':
                suits[0]++;
                break;
            case 'H':
                suits[1]++;
                break;
            case 'D':
                suits[2]++;
                break;
            case 'C':
                suits[3]++;
                break;
        }
    }

    for (int i = 0; i < handSize; i++) {
        switch (hand[i][strlen(hand[i]) - 1]) {
            case 'S':
                suits[0]++;
                break;
            case 'H':
                suits[1]++;
                break;
            case 'D':
                suits[2]++;
                break;
            case 'C':
                suits[3]++;
                break;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (suits[i] >= 5) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char table1[5][5] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char hand1[2][5] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1, 5, 2)); // true

    char table2[5][5] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char hand2[2][5] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2, 5, 2)); // true

    char table3[5][5] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char hand3[2][5] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3, 5, 2)); // false

    char table4[5][5] = {"2_H", "3_H", "4_H", "5_H", "6_D"};
    char hand4[2][5] = {"7_H", "8_C"};
    printf("%d\n", checkFlush(table4, hand4, 5, 2)); // true

    char table5[5][5] = {"2_D", "4_S", "5_C", "8_D", "K_H"};
    char hand5[2][5] = {"Q_H", "3_D"};
    printf("%d\n", checkFlush(table5, hand5, 5, 2)); // false

    return 0;
}