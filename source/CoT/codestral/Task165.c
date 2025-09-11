#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkFlush(const char* table[], const char* hand[], int tableSize, int handSize) {
    int spades = 0, hearts = 0, diamonds = 0, clubs = 0;

    for (int i = 0; i < tableSize; i++) {
        if (table[i][strlen(table[i]) - 1] == 'S') spades++;
        else if (table[i][strlen(table[i]) - 1] == 'H') hearts++;
        else if (table[i][strlen(table[i]) - 1] == 'D') diamonds++;
        else if (table[i][strlen(table[i]) - 1] == 'C') clubs++;
    }

    for (int i = 0; i < handSize; i++) {
        if (hand[i][strlen(hand[i]) - 1] == 'S') spades++;
        else if (hand[i][strlen(hand[i]) - 1] == 'H') hearts++;
        else if (hand[i][strlen(hand[i]) - 1] == 'D') diamonds++;
        else if (hand[i][strlen(hand[i]) - 1] == 'C') clubs++;
    }

    return spades >= 5 || hearts >= 5 || diamonds >= 5 || clubs >= 5;
}

int main() {
    const char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1, 5, 2)); // 1 (true)

    const char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2, 5, 2)); // 1 (true)

    const char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3, 5, 2)); // 0 (false)

    return 0;
}