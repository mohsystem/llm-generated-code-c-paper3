
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void setTime(Clock* clock, int hours, int minutes) {
    int totalMinutes = hours * 60 + minutes;
    
    // Handle negative time
    while (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }
    
    totalMinutes = totalMinutes % (24 * 60);
    clock->hours = totalMinutes / 60;
    clock->minutes = totalMinutes % 60;
}

void initClock(Clock* clock, int hours, int minutes) {
    setTime(clock, hours, minutes);
}

void addMinutes(Clock* clock, int minutes) {
    setTime(clock, clock->hours, clock->minutes + minutes);
}

void subtractMinutes(Clock* clock, int minutes) {
    addMinutes(clock, -minutes);
}

bool clocksEqual(const Clock* clock1, const Clock* clock2) {
    return clock1->hours == clock2->hours && clock1->minutes == clock2->minutes;
}

void printClock(const Clock* clock) {
    printf("%02d:%02d", clock->hours, clock->minutes);
}

int main() {
    // Test case 1: Basic clock creation
    Clock clock1;
    initClock(&clock1, 10, 30);
    printf("Test 1: ");
    printClock(&clock1);
    printf("\\n");
    
    // Test case 2: Adding minutes
    Clock clock2;
    initClock(&clock2, 10, 30);
    addMinutes(&clock2, 60);
    printf("Test 2: ");
    printClock(&clock2);
    printf("\\n");
    
    // Test case 3: Subtracting minutes
    Clock clock3;
    initClock(&clock3, 10, 30);
    subtractMinutes(&clock3, 60);
    printf("Test 3: ");
    printClock(&clock3);
    printf("\\n");
    
    // Test case 4: Handling overflow
    Clock clock4;
    initClock(&clock4, 23, 45);
    addMinutes(&clock4, 20);
    printf("Test 4: ");
    printClock(&clock4);
    printf("\\n");
    
    // Test case 5: Equality test
    Clock clock5a, clock5b;
    initClock(&clock5a, 10, 30);
    initClock(&clock5b, 10, 30);
    printf("Test 5: %d\\n", clocksEqual(&clock5a, &clock5b));
    
    return 0;
}
