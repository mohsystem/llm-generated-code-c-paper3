#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

Task199 createClock(int hours, int minutes) {
    Task199 clock;
    clock.hours = (hours + (minutes / 60)) % 24;
    clock.minutes = minutes % 60;
    return clock;
}

void addMinutes(Task199* clock, int minutes) {
    clock->minutes += minutes;
    clock->hours += clock->minutes / 60;
    clock->hours %= 24;
    clock->minutes %= 60;
}

void subtractMinutes(Task199* clock, int minutes) {
    clock->minutes -= minutes;
    if (clock->minutes < 0) {
        clock->hours -= 1;
        clock->minutes += 60;
    }
    if (clock->hours < 0) {
        clock->hours += 24;
    }
}

bool areClocksEqual(Task199 clock1, Task199 clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

int main() {
    Task199 clock1 = createClock(10, 30);
    Task199 clock2 = createClock(10, 30);
    Task199 clock3 = createClock(11, 30);

    printf("%d\n", areClocksEqual(clock1, clock2));  // 1 (true)
    printf("%d\n", areClocksEqual(clock1, clock3));  // 0 (false)

    addMinutes(&clock1, 90);
    printf("%d\n", areClocksEqual(clock1, clock3));  // 1 (true)

    subtractMinutes(&clock3, 30);
    printf("%d\n", areClocksEqual(clock1, clock3));  // 0 (false)

    return 0;
}