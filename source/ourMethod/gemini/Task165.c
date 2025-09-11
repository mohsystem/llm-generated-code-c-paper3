#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkFlush(char table[][4], char hand[][4], int tableSize, int handSize) {
    int suitCounts[4] = {0}; // Spades, Hearts, Diamonds, Clubs

    for (int i = 0; i < tableSize; i++) {
        char suit = table[i][2];
        if (suit == 'S') suitCounts[0]++;
        else if (suit == 'H') suitCounts[1]++;
        else if (suit == 'D') suitCounts[2]++;
        else if (suit == 'C') suitCounts[3]++;
    }

    for (int i = 0; i < handSize; i++) {
        char suit = hand[i][2];
        if (suit == 'S') suitCounts[0]++;
        else if (suit == 'H') suitCounts[1]++;
        else if (suit == 'D') suitCounts[2]++;
        else if (suit == 'C') suitCounts[3]++;
    }

    for (int i = 0; i < 4; i++) {
        if (suitCounts[i] >= 5) {
            return true;
        }
    }

    return false;
}

int main() {
    char table1[][4] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char hand1[][4] = {"J_D", "3_D"};
    printf("%s\n", checkFlush(table1, hand1, 5, 2) ? "true" : "false"); // true

    char table2[][4] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char hand2[][4] = {"K_S", "Q_S"};
    printf("%s\n", checkFlush(table2, hand2, 5, 2) ? "true" : "false"); // true

    char table3[][4] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char hand3[][4] = {"3_S", "4_D"};
    printf("%s\n", checkFlush(table3, hand3, 5, 2) ? "true" : "false"); // false

        char table4[][4] = {"2_H", "5_H", "A_H", "9_H", "J_H"};
    char hand4[][4] = {"2_D", "3_H"};
    printf("%s\n", checkFlush(table4, hand4, 5, 2) ? "true" : "false"); // true
    
    char table5[][4] = {"K_C", "10_C", "8_C", "9_C", "J_C"};
    char hand5[][4] = {"Q_C", "A_C"};
    printf("%s\n", checkFlush(table5, hand5, 5, 2) ? "true" : "false"); // true


    return 0;
}