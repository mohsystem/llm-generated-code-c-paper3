#include <stdio.h>
#include <string.h>

int checkFlush(const char* tableCards[], int tableSize, const char* handCards[], int handSize) {
    int suitCount[4] = {0}; // 0: S, 1: H, 2: D, 3: C

    for (int i = 0; i < tableSize; ++i) {
        char suit = tableCards[i][strlen(tableCards[i]) - 1];
        if (suit == 'S') suitCount[0]++;
        else if (suit == 'H') suitCount[1]++;
        else if (suit == 'D') suitCount[2]++;
        else if (suit == 'C') suitCount[3]++;
    }

    for (int i = 0; i < handSize; ++i) {
        char suit = handCards[i][strlen(handCards[i]) - 1];
        if (suit == 'S') suitCount[0]++;
        else if (suit == 'H') suitCount[1]++;
        else if (suit == 'D') suitCount[2]++;
        else if (suit == 'C') suitCount[3]++;
    }

    for (int i = 0; i < 4; ++i) {
        if (suitCount[i] >= 5) {
            return 1;
        }
    }

    return 0;
}

int main() {
    const char* table1[] = {"A_S", "J_H", "7_D", "8_D", "10_D"};
    const char* hand1[] = {"J_D", "3_D"};
    printf("%d\n", checkFlush(table1, 5, hand1, 2)); // 1 (true)

    const char* table2[] = {"10_S", "7_S", "9_H", "4_S", "3_S"};
    const char* hand2[] = {"K_S", "Q_S"};
    printf("%d\n", checkFlush(table2, 5, hand2, 2)); // 1 (true)

    const char* table3[] = {"3_S", "10_H", "10_D", "10_C", "10_S"};
    const char* hand3[] = {"3_S", "4_D"};
    printf("%d\n", checkFlush(table3, 5, hand3, 2)); // 0 (false)

    const char* table4[] = {"A_H", "2_H", "3_H", "4_C", "5_D"};
    const char* hand4[] = {"6_H", "7_H"};
    printf("%d\n", checkFlush(table4, 5, hand4, 2)); // 1 (true)

    const char* table5[] = {"A_S", "K_S", "Q_S", "J_S", "10_H"};
    const char* hand5[] = {"9_S", "8_S"};
    printf("%d\n", checkFlush(table5, 5, hand5, 2)); // 1 (true)

    return 0;
}