#include <stdio.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void initClock(Clock* clock, int hours, int minutes) {
    clock->hours = hours;
    clock->minutes = minutes;
    normalize(clock);
}

void addMinutes(Clock* clock, int minutes) {
    clock->minutes += minutes;
    normalize(clock);
}

void subtractMinutes(Clock* clock, int minutes) {
    clock->minutes -= minutes;
    normalize(clock);
}

int areClocksEqual(const Clock* clock1, const Clock* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void printClock(const Clock* clock) {
    printf("%02d:%02d\n", clock->hours, clock->minutes);
}

void normalize(Clock* clock) {
    clock->hours += clock->minutes / 60;
    clock->minutes %= 60;
    clock->hours %= 24;
}

int main() {
    Clock clock1, clock2, clock3;

    initClock(&clock1, 12, 30);
    initClock(&clock2, 12, 30);
    initClock(&clock3, 12, 31);

    printClock(&clock1); // Output: 12:30
    printClock(&clock2); // Output: 12:30
    printClock(&clock3); // Output: 12:31

    addMinutes(&clock1, 30);
    printClock(&clock1); // Output: 13:00

    subtractMinutes(&clock2, 60);
    printClock(&clock2); // Output: 11:30

    printf("%d\n", areClocksEqual(&clock1, &clock2)); // Output: 0 (False)
    printf("%d\n", areClocksEqual(&clock1, &clock3)); // Output: 0 (False)
    printf("%d\n", areClocksEqual(&clock2, &clock3)); // Output: 0 (False)
    printf("%d\n", areClocksEqual(&clock1, &clock1)); // Output: 1 (True)
    printf("%d\n", areClocksEqual(&clock2, &clock2)); // Output: 1 (True)

    return 0;
}