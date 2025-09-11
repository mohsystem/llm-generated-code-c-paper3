#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

Task199 createClock(int hours, int minutes) {
    Task199 clock;
    clock.hours = hours;
    clock.minutes = minutes;
    normalize(&clock);
    return clock;
}

void addMinutes(Task199* clock, int minutes) {
    clock->minutes += minutes;
    normalize(clock);
}

void subtractMinutes(Task199* clock, int minutes) {
    clock->minutes -= minutes;
    normalize(clock);
}

bool areEqual(Task199 clock1, Task199 clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

void normalize(Task199* clock) {
    while (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours--;
    }
    while (clock->minutes >= 60) {
        clock->minutes -= 60;
        clock->hours++;
    }
    clock->hours = (clock->hours % 24 + 24) % 24;
}

int main() {
    Task199 clock1 = createClock(10, 30);
    Task199 clock2 = createClock(10, 30);
    Task199 clock3 = createClock(11, 30);

    addMinutes(&clock1, 30);
    subtractMinutes(&clock2, 15);

    printf("%d\n", areEqual(clock1, clock2));  // 1 (True)
    printf("%d\n", areEqual(clock1, clock3));  // 0 (False)

    return 0;
}