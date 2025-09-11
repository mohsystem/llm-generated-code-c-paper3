#include <stdio.h>
#include <string.h>

int checkFlush(char *tableCards[], char *handCards[], int tableSize, int handSize) {
    int suitCount[4] = {0}; // S, H, D, C
    char suits[] = {'S', 'H', 'D', 'C'};
    
    for (int i = 0; i < tableSize; i++) {
        char *suit = strchr(tableCards[i], '_') + 1;
        for (int j = 0; j < 4; j++) {
            if (*suit == suits[j]) {
                suitCount[j]++;
                break;
            }
        }
    }

    for (int i = 0; i < handSize; i++) {
        char *suit = strchr(handCards[i], '_') + 1;
        for (int j = 0; j < 4; j++) {
            if (*suit == suits[j]) {
                suitCount[j]++;
                break;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (suitCount[i] >= 5) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char *table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    char *hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, hand1, 5, 2)); // 1

    char *table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    char *hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, hand2, 5, 2)); // 1

    char *table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    char *hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, hand3, 5, 2)); // 0

    char *table4[] = {"2_H", "3_H", "4_H", "5_H", "6_H"};
    char *hand4[] = {"7_H", "8_H"};
    printf("%d\n", checkFlush(table4, hand4, 5, 2)); // 1

    char *table5[] = {"2_D", "3_C", "4_S", "5_S", "6_S"};
    char *hand5[] = {"7_D", "8_D"};
    printf("%d\n", checkFlush(table5, hand5, 5, 2)); // 0

    return 0;
}