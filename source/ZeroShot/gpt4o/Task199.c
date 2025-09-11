#include <stdio.h>

typedef struct {
    int minutes;
} Clock;

Clock createClock(int hours, int minutes) {
    Clock clock;
    clock.minutes = (hours * 60 + minutes) % 1440;
    if (clock.minutes < 0) {
        clock.minutes += 1440;
    }
    return clock;
}

Clock addMinutes(Clock clock, int minutesToAdd) {
    return createClock(0, clock.minutes + minutesToAdd);
}

Clock subtractMinutes(Clock clock, int minutesToSubtract) {
    return createClock(0, clock.minutes - minutesToSubtract);
}

int equals(Clock clock1, Clock clock2) {
    return clock1.minutes == clock2.minutes;
}

void printClock(Clock clock) {
    int hours = (clock.minutes / 60) % 24;
    int mins = clock.minutes % 60;
    printf("%02d:%02d\n", hours, mins);
}

int main() {
    Clock clock1 = createClock(10, 0);
    Clock clock2 = addMinutes(clock1, 150);
    Clock clock3 = subtractMinutes(clock1, 60);
    Clock clock4 = createClock(12, 30);
    Clock clock5 = createClock(10, 0);

    printClock(clock1); // 10:00
    printClock(clock2); // 12:30
    printClock(clock3); // 09:00
    printf("%d\n", equals(clock1, clock5)); // 1 (true)
    printf("%d\n", equals(clock1, clock4)); // 0 (false)

    return 0;
}