
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void normalize(Clock* clock) {
    while (clock->minutes < 0) {
        clock->minutes += 60;
        clock->hours--;
    }
    
    int total_hours = clock->hours + clock->minutes / 60;
    clock->minutes = clock->minutes % 60;
    while (total_hours < 0) {
        total_hours += 24;
    }
    clock->hours = total_hours % 24;
}

Clock createClock(int hours, int minutes) {
    Clock clock = {hours, minutes};
    normalize(&clock);
    return clock;
}

void addMinutes(Clock* clock, int minutesToAdd) {
    clock->minutes += minutesToAdd;
    normalize(clock);
}

void subtractMinutes(Clock* clock, int minutesToSubtract) {
    clock->minutes -= minutesToSubtract;
    normalize(clock);
}

bool isEqual(Clock clock1, Clock clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

void printClock(Clock clock) {
    printf("%02d:%02d", clock.hours, clock.minutes);
}

int main() {
    // Test case 1: Basic clock creation
    Clock clock1 = createClock(8, 0);
    printf("Test 1: ");
    printClock(clock1);
    printf("\\n");

    // Test case 2: Adding minutes
    Clock clock2 = createClock(8, 0);
    addMinutes(&clock2, 65);
    printf("Test 2: ");
    printClock(clock2);
    printf("\\n");

    // Test case 3: Subtracting minutes
    Clock clock3 = createClock(8, 0);
    subtractMinutes(&clock3, 65);
    printf("Test 3: ");
    printClock(clock3);
    printf("\\n");

    // Test case 4: Equality check
    Clock clock4a = createClock(14, 30);
    Clock clock4b = createClock(14, 30);
    printf("Test 4: %d\\n", isEqual(clock4a, clock4b));

    // Test case 5: Wrapping around midnight
    Clock clock5 = createClock(23, 45);
    addMinutes(&clock5, 30);
    printf("Test 5: ");
    printClock(clock5);
    printf("\\n");

    return 0;
}
