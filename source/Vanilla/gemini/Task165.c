#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkFlush(char table[5][4], char hand[2][4]) {
    int suitCounts[4] = {0}; // S, H, D, C
    for (int i = 0; i < 5; i++) {
        char suit = table[i][strlen(table[i]) - 1];
        if (suit == 'S') suitCounts[0]++;
        else if (suit == 'H') suitCounts[1]++;
        else if (suit == 'D') suitCounts[2]++;
        else if (suit == 'C') suitCounts[3]++;
    }
    for (int i = 0; i < 2; i++) {
        char suit = hand[i][strlen(hand[i]) - 1];
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
    printf("%d\n", checkFlush({"A_S", "J_H", "7_D", "8_D", "10_D"}, {"J_D", "3_D"})); // true
    printf("%d\n", checkFlush({"10_S", "7_S", "9_H", "4_S", "3_S"}, {"K_S", "Q_S"})); // true
    printf("%d\n", checkFlush({"3_S", "10_H", "10_D", "10_C", "10_S"}, {"3_S", "4_D"})); // false
    printf("%d\n", checkFlush({"2_H", "5_H", "7_H", "9_H", "J_H"}, {"2_D", "5_D"})); //true
    printf("%d\n", checkFlush({"A_S", "2_S", "3_S", "4_H", "5_H"}, {"6_H", "7_H"})); //false

    return 0;
}