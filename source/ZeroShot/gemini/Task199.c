#include <stdio.h>
#include <stdbool.h>

struct Clock {
    int minutes;
};

struct Clock createClock(int hours, int minutes) {
    struct Clock clock;
    clock.minutes = (hours * 60 + minutes) % 1440;
    if (clock.minutes < 0) {
        clock.minutes += 1440;
    }
    return clock;
}

void add(struct Clock *clock, int minutes) {
    clock->minutes = (clock->minutes + minutes) % 1440;
    if (clock->minutes < 0) {
        clock->minutes += 1440;
    }
}

void subtract(struct Clock *clock, int minutes) {
    add(clock, -minutes);
}

bool isEqual(struct Clock clock1, struct Clock clock2) {
    return clock1.minutes == clock2.minutes;
}

void printClock(struct Clock clock) {
    int hours = (clock.minutes / 60) % 24;
    int mins = clock.minutes % 60;
    printf("%02d:%02d\n", hours, mins);
}


int main() {
    struct Clock clock1 = createClock(10, 30);
    struct Clock clock2 = createClock(10, 30);
    printf("%s\n", isEqual(clock1, clock2) ? "true" : "false"); // true

    add(&clock1, 30);
    printClock(clock1); // 11:00

    subtract(&clock1, 60);
    printClock(clock1); // 10:00

    struct Clock clock3 = createClock(23, 59);
    add(&clock3, 1);
    printClock(clock3); // 00:00


    struct Clock clock4 = createClock(0, 0);
    subtract(&clock4, 1);
    printClock(clock4); // 23:59
    return 0;
}