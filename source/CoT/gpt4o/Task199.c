#include <stdio.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void add_minutes(Clock* clock, int minutes_to_add) {
    int total_minutes = clock->hours * 60 + clock->minutes + minutes_to_add;
    clock->hours = (total_minutes / 60) % 24;
    clock->minutes = total_minutes % 60;
}

void subtract_minutes(Clock* clock, int minutes_to_subtract) {
    add_minutes(clock, -minutes_to_subtract);
}

int clocks_equal(Clock* clock1, Clock* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void print_clock(Clock* clock) {
    printf("%02d:%02d\n", clock->hours, clock->minutes);
}

int main() {
    Clock clock1 = {10, 0};
    Clock clock2 = {9, 60};
    Clock clock3 = {23, 59};
    Clock clock4 = {0, 1};
    Clock clock5 = {24, 0};

    add_minutes(&clock1, 20);
    subtract_minutes(&clock2, 60);
    add_minutes(&clock3, 2);
    subtract_minutes(&clock4, 2);
    add_minutes(&clock5, -1440);

    print_clock(&clock1); // Should print 10:20
    print_clock(&clock2); // Should print 09:00
    print_clock(&clock3); // Should print 00:01
    print_clock(&clock4); // Should print 23:59
    print_clock(&clock5); // Should print 00:00

    printf("%d\n", clocks_equal(&clock1, &clock2)); // Should print 0 (false)
    printf("%d\n", clocks_equal(&clock2, &(Clock){9, 0})); // Should print 1 (true)

    return 0;
}