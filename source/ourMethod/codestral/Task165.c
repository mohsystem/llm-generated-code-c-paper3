#include <stdio.h>
#include <string.h>

#define MAX_CARDS 7
#define SUITS 4

int checkFlush(char* table[], char* hand[], int tableSize, int handSize) {
    int suitCount[SUITS] = {0};
    for (int i = 0; i < tableSize; i++) {
        char suit = table[i][strlen(table[i]) - 1];
        switch (suit) {
            case 'S':
                suitCount[0]++;
                break;
            case 'H':
                suitCount[1]++;
                break;
            case 'D':
                suitCount[2]++;
                break;
            case 'C':
                suitCount[3]++;
                break;
        }
        if (suitCount[suit - 'S'] >= 3) {
            return 1;
        }
    }
    for (int i = 0; i < handSize; i++) {
        char suit = hand[i][strlen(hand[i]) - 1];
        switch (suit) {
            case 'S':
                suitCount[0]++;
                break;
            case 'H':
                suitCount[1]++;
                break;
            case 'D':
                suitCount[2]++;
                break;
            case 'C':
                suitCount[3]++;
                break;
        }
        if (suitCount[suit - 'S'] >= 3) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1, 5, 2));

    char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2, 5, 2));

    char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3, 5, 2));

    return 0;
}