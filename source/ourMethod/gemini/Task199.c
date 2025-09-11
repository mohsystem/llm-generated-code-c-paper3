#include <stdio.h>
#include <stdbool.h>

struct Task199 {
    int hours;
    int minutes;
};

void add(struct Task199 *clock, int minutes) {
    clock->minutes += minutes;
    clock->hours += clock->minutes / 60;
    clock->hours %= 24;
    clock->minutes %= 60;
    if (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours--;
        if (clock->hours < 0) {
            clock->hours += 24;
        }
    }
}

void subtract(struct Task199 *clock, int minutes) {
    add(clock, -minutes);
}

bool equals(struct Task199 clock1, struct Task199 clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}


int main() {
    struct Task199 clock1 = {10, 30};
    printf("%02d:%02d\n", clock1.hours, clock1.minutes); // Output: 10:30
    add(&clock1, 20);
    printf("%02d:%02d\n", clock1.hours, clock1.minutes); // Output: 10:50

    struct Task199 clock2 = {23, 50};
    printf("%02d:%02d\n", clock2.hours, clock2.minutes); // Output: 23:50
    add(&clock2, 20);
    printf("%02d:%02d\n", clock2.hours, clock2.minutes); // Output: 00:10

    struct Task199 clock3 = {10, 30};
    printf("%d\n", equals(clock3, clock1)); // Output: 0 (false)
    
    struct Task199 clock4 = {10, 30};
    add(&clock4, 150);
    printf("%02d:%02d\n", clock4.hours, clock4.minutes); // Output: 12:00

    struct Task199 clock5 = {1, 30};
    subtract(&clock5, 90);
    printf("%02d:%02d\n", clock5.hours, clock5.minutes); // Output: 22:00

    return 0;
}