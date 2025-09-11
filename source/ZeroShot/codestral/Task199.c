#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Task199;

Task199 createClock(int hours, int minutes) {
    Task199 clock;
    clock.hours = (hours + minutes / 60) % 24;
    clock.minutes = minutes % 60;
    return clock;
}

void addMinutes(Task199 *clock, int minutes) {
    clock->minutes += minutes;
    clock->hours += clock->minutes / 60;
    clock->hours %= 24;
    clock->minutes %= 60;
}

void subtractMinutes(Task199 *clock, int minutes) {
    clock->minutes -= minutes;
    if (clock->minutes < 0) {
        clock->hours += (clock->minutes / 60) - 1;
        clock->minutes = 60 + (clock->minutes % 60);
    }
    clock->hours %= 24;
    if (clock->hours < 0) clock->hours = 24 + clock->hours;
}

bool equals(Task199 clock1, Task199 clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

int main() {
    Task199 clock1 = createClock(12, 30);
    Task199 clock2 = createClock(12, 30);
    Task199 clock3 = createClock(13, 30);

    printf("%d\n", equals(clock1, clock2)); // 1 (true)
    printf("%d\n", equals(clock1, clock3)); // 0 (false)

    addMinutes(&clock1, 30);
    printf("%d\n", equals(clock1, clock3)); // 1 (true)

    subtractMinutes(&clock1, 60);
    printf("%d\n", equals(clock1, clock2)); // 1 (true)

    return 0;
}