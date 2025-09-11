#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int minutes;
} Clock;

void initClock(Clock* clock, int minutes) {
    clock->minutes = minutes % 1440;
}

void addMinutes(Clock* clock, int minutes) {
    clock->minutes = (clock->minutes + minutes) % 1440;
}

void subtractMinutes(Clock* clock, int minutes) {
    clock->minutes = (clock->minutes - minutes + 1440) % 1440;
}

bool areClocksEqual(const Clock* clock1, const Clock* clock2) {
    return clock1->minutes == clock2->minutes;
}

void printClock(const Clock* clock) {
    int hours = clock->minutes / 60;
    int mins = clock->minutes % 60;
    printf("%02d:%02d", hours, mins);
}

int main() {
    Clock clock1, clock2, clock3;

    initClock(&clock1, 120); // 2:00
    initClock(&clock2, 120); // 2:00
    initClock(&clock3, 121); // 2:01

    printf("Clock1: ");
    printClock(&clock1);
    printf("\n");

    printf("Clock2: ");
    printClock(&clock2);
    printf("\n");

    printf("Clock3: ");
    printClock(&clock3);
    printf("\n");

    addMinutes(&clock1, 30);
    printf("Clock1 after adding 30 minutes: ");
    printClock(&clock1);
    printf("\n");

    subtractMinutes(&clock2, 30);
    printf("Clock2 after subtracting 30 minutes: ");
    printClock(&clock2);
    printf("\n");

    printf("Are Clock1 and Clock2 equal? %d\n", areClocksEqual(&clock1, &clock2));
    printf("Are Clock1 and Clock3 equal? %d\n", areClocksEqual(&clock1, &clock3));

    return 0;
}