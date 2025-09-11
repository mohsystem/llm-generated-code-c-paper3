#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void initClock(Clock* clock, int hours, int minutes) {
    clock->hours = hours;
    clock->minutes = minutes;
    normalizeClock(clock);
}

void addMinutes(Clock* clock, int minutes) {
    clock->minutes += minutes;
    normalizeClock(clock);
}

void subtractMinutes(Clock* clock, int minutes) {
    clock->minutes -= minutes;
    normalizeClock(clock);
}

void normalizeClock(Clock* clock) {
    int totalMinutes = clock->hours * 60 + clock->minutes;
    clock->hours = totalMinutes / 60 % 24;
    clock->minutes = totalMinutes % 60;
}

bool areClocksEqual(const Clock* clock1, const Clock* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void printClock(const Clock* clock) {
    printf("%02d:%02d", clock->hours, clock->minutes);
}

int main() {
    Clock clock1, clock2, clock3;

    initClock(&clock1, 12, 30);
    initClock(&clock2, 12, 30);
    initClock(&clock3, 12, 45);

    printClock(&clock1); printf("\n");  // Output: 12:30
    addMinutes(&clock1, 15);
    printClock(&clock1); printf("\n");  // Output: 12:45
    subtractMinutes(&clock1, 15);
    printClock(&clock1); printf("\n");  // Output: 12:30

    printf("%d\n", areClocksEqual(&clock1, &clock2));  // Output: 1
    printf("%d\n", areClocksEqual(&clock1, &clock3));  // Output: 0

    return 0;
}