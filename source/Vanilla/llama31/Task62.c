// C does not have a built-in JSON parsing library, so this is a simplified example.
// For full JSON parsing, you would need to implement or use a third-party library.

#include <stdio.h>
#include <string.h>

// Simplified function to find the first key in a JSON string
char* getRootElement(char* jsonString) {
    char* start = strstr(jsonString, "{");
    if (start == NULL) return "Invalid JSON";

    start++; // Move past the '{'
    char* end = strchr(start, ':');
    if (end == NULL) return "Invalid JSON";

    *end = '\0'; // Temporarily null-terminate the string
    char* rootElement = start;
    *end = ':'; // Restore the original character

    return rootElement;
}

int main() {
    char* testCases[] = {
        "{\"name\": \"Susan Smith\", \"org\": \"engineering\", \"projects\": [{\"name\":\"project1\", \"completed\":false}, {\"name\":\"project2\", \"completed\":true}]}",
        "{\"store\": {\"book\": [{\"category\": \"reference\", \"author\": \"Nigel Rees\", \"title\": \"Sayings of the Century\", \"price\": 8.95}]}",
        "{\"event\": {\"agency\": \"MI6\", \"data\": {\"name\": \"James Bond\", \"id\": \"007\"}}}",
        "{\"person\": {\"name\": \"John Doe\", \"age\": 30}}",
        "Invalid JSON"
    };

    for (int i = 0; i < 5; i++) {
        printf("Root Element: %s\n", getRootElement(testCases[i]));
    }

    return 0;
}