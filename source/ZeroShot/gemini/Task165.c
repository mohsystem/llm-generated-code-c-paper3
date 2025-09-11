#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkFlush(char table[5][4], char hand[2][4]) {
    int suitCounts[4] = {0}; // S, H, D, C
    for (int i = 0; i < 5; i++) {
        char suit = table[i][2];
        if (suit == 'S') suitCounts[0]++;
        else if (suit == 'H') suitCounts[1]++;
        else if (suit == 'D') suitCounts[2]++;
        else if (suit == 'C') suitCounts[3]++;
    }
    for (int i = 0; i < 2; i++) {
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
    printf("%d\n", checkFlush((char[][4]){"A_S", "J_H", "7_D", "8_D", "10_D"}, (char[][4]){"J_D", "3_D"})); // true
    printf("%d\n", checkFlush((char[][4]){"10_S", "7_S", "9_H", "4_S", "3_S"}, (char[][4]){"K_S", "Q_S"})); // true
    printf("%d\n", checkFlush((char[][4]){"3_S", "10_H", "10_D", "10_C", "10_S"}, (char[][4]){"3_S", "4_D"})); // false
    printf("%d\n", checkFlush((char[][4]){"2_H", "5_H", "A_H", "K_H", "J_H"}, (char[][4]){"2_D", "3_S"})); // true
    printf("%d\n", checkFlush((char[][4]){"A_S", "K_H", "Q_D", "J_C", "10_S"}, (char[][4]){"Q_S", "J_S"})); // false

    return 0;
}