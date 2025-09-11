
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hours;
    int minutes;
} Clock;

void setTime(Clock* clock, int hours, int minutes) {
    int totalMinutes = ((hours * 60 + minutes) % (24 * 60));
    if (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }
    clock->hours = (totalMinutes / 60) % 24;
    clock->minutes = totalMinutes % 60;
}

Clock createClock(int hours, int minutes) {
    Clock clock;
    setTime(&clock, hours, minutes);
    return clock;
}

void addMinutes(Clock* clock, int minutes) {
    setTime(clock, clock->hours, clock->minutes + minutes);
}

void subtractMinutes(Clock* clock, int minutes) {
    addMinutes(clock, -minutes);
}

bool isEqual(Clock clock1, Clock clock2) {
    return clock1.hours == clock2.hours && clock1.minutes == clock2.minutes;
}

void toString(Clock clock, char* buffer) {
    sprintf(buffer, "%02d:%02d", clock.hours, clock.minutes);
}

int main() {
    char buffer[6];
    
    // Test case 1: Basic clock creation
    Clock clock1 = createClock(8, 0);
    toString(clock1, buffer);
    printf("Test 1: %s\\n", buffer);
    
    // Test case 2: Adding minutes
    Clock clock2 = createClock(11, 9);
    addMinutes(&clock2, 200);
    toString(clock2, buffer);
    printf("Test 2: %s\\n", buffer);
    
    // Test case 3: Subtracting minutes
    Clock clock3 = createClock(10, 30);
    subtractMinutes(&clock3, 90);
    toString(clock3, buffer);
    printf("Test 3: %s\\n", buffer);
    
    // Test case 4: Equality test
    Clock clock4a = createClock(23, 59);
    Clock clock4b = createClock(23, 59);
    printf("Test 4: %d\\n", isEqual(clock4a, clock4b));
    
    // Test case 5: Handling negative values
    Clock clock5 = createClock(-1, -40);
    toString(clock5, buffer);
    printf("Test 5: %s\\n", buffer);
    
    return 0;
}
