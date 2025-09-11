#include <stdio.h>
#include <string.h>

#define MAX_CARDS 7

int checkFlush(char *table[], int tableSize, char *hand[], int handSize) {
    int suits[4] = {0};
    for (int i = 0; i < tableSize; i++) {
        char suit = table[i][strlen(table[i]) - 1];
        switch (suit) {
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
        char suit = hand[i][strlen(hand[i]) - 1];
        switch (suit) {
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
    char *table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char *hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, 5, hand1, 2));  // 1 (true)

    char *table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char *hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, 5, hand2, 2));  // 1 (true)

    char *table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char *hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, 5, hand3, 2));  // 0 (false)

    return 0;
}