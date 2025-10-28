#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct JSONElement {
    char type[20];
    char* stringValue;
    void* complexValue;
} JSONElement;

typedef struct ParseResult {
    JSONElement* element;
    int endIndex;
} ParseResult;

JSONElement* createJSONElement(const char* type, const char* value) {
    JSONElement* elem = (JSONElement*)malloc(sizeof(JSONElement));
    strcpy(elem->type, type);
    if (value) {
        elem->stringValue = (char*)malloc(strlen(value) + 1);
        strcpy(elem->stringValue, value);
    } else {
        elem->stringValue = NULL;
    }
    elem->complexValue = NULL;
    return elem;
}

ParseResult parseValue(const char* json, int start);

ParseResult parseString(const char* json, int start) {
    char buffer[1000];
    int bufIndex = 0;
    int i = start + 1;

    while (i < (int)strlen(json) && json[i] != '"') {
        if (json[i] == '\\' && i + 1 < (int)strlen(json)) {
            i++;
        }
        buffer[bufIndex++] = json[i];
        i++;
    }
    buffer[bufIndex] = '\0';

    ParseResult result;
    result.element = createJSONElement("string", buffer);
    result.endIndex = i + 1;
    return result;
}

ParseResult parseNumber(const char* json, int start) {
    char buffer[100];
    int bufIndex = 0;
    int i = start;

    while (i < (int)strlen(json) &&
           (isdigit((unsigned char)json[i]) || json[i] == '-' || json[i] == '.' ||
            json[i] == 'e' || json[i] == 'E' || json[i] == '+')) {
        buffer[bufIndex++] = json[i];
        i++;
    }
    buffer[bufIndex] = '\0';

    ParseResult result;
    result.element = createJSONElement("number", buffer);
    result.endIndex = i;
    return result;
}

ParseResult parseBoolean(const char* json, int start) {
    ParseResult result;
    if (strncmp(&json[start], "true", 4) == 0) {
        result.element = createJSONElement("boolean", "true");
        result.endIndex = start + 4;
    } else if (strncmp(&json[start], "false", 5) == 0) {
        result.element = createJSONElement("boolean", "false");
        result.endIndex = start + 5;
    } else {
        result.element = createJSONElement("null", NULL);
        result.endIndex = start;
    }
    return result;
}

ParseResult parseNull(const char* json, int start) {
    ParseResult result;
    if (strncmp(&json[start], "null", 4) == 0) {
        result.element = createJSONElement("null", NULL);
        result.endIndex = start + 4;
    } else {
        result.element = createJSONElement("null", NULL);
        result.endIndex = start;
    }
    return result;
}

ParseResult parseObject(const char* json, int start) {
    ParseResult result;
    result.element = createJSONElement("object", "{...}");
    int i = start + 1;

    while (i < (int)strlen(json)) {
        while (i < (int)strlen(json) && isspace((unsigned char)json[i])) i++;
        if (i < (int)strlen(json) && json[i] == '}') {
            result.endIndex = i + 1;
            return result;
        }

        ParseResult keyResult = parseString(json, i);
        i = keyResult.endIndex;

        while (i < (int)strlen(json) && isspace((unsigned char)json[i])) i++;
        if (i < (int)strlen(json) && json[i] == ':') i++;

        ParseResult valueResult = parseValue(json, i);
        i = valueResult.endIndex;

        while (i < (int)strlen(json) && isspace((unsigned char)json[i])) i++;
        if (i < (int)strlen(json) && json[i] == ',') i++;
    }

    result.endIndex = i;
    return result;
}

ParseResult parseArray(const char* json, int start) {
    ParseResult result;
    result.element = createJSONElement("array", "[...]");
    int i = start + 1;

    while (i < (int)strlen(json)) {
        while (i < (int)strlen(json) && isspace((unsigned char)json[i])) i++;
        if (i < (int)strlen(json) && json[i] == ']') {
            result.endIndex = i + 1;
            return result;
        }

        ParseResult valueResult = parseValue(json, i);
        i = valueResult.endIndex;

        while (i < (int)strlen(json) && isspace((unsigned char)json[i])) i++;
        if (i < (int)strlen(json) && json[i] == ',') i++;
    }

    result.endIndex = i;
    return result;
}

ParseResult parseValue(const char* json, int start) {
    while (start < (int)strlen(json) && isspace((unsigned char)json[start])) start++;

    ParseResult result;
    if (start >= (int)strlen(json)) {
        result.element = createJSONElement("null", NULL);
        result.endIndex = start;
        return result;
    }

    char ch = json[start];

    if (ch == '{') {
        return parseObject(json, start);
    } else if (ch == '[') {
        return parseArray(json, start);
    } else if (ch == '"') {
        return parseString(json, start);
    } else if (ch == 't' || ch == 'f') {
        return parseBoolean(json, start);
    } else if (ch == 'n') {
        return parseNull(json, start);
    } else if (ch == '-' || isdigit((unsigned char)ch)) {
        return parseNumber(json, start);
    }

    result.element = createJSONElement("null", NULL);
    result.endIndex = start;
    return result;
}

JSONElement* parseAndGetRoot(const char* jsonString) {
    if (!jsonString || strlen(jsonString) == 0) {
        return createJSONElement("null", NULL);
    }

    ParseResult result = parseValue(jsonString, 0);
    return result.element;
}

void printJSONElement(JSONElement* elem) {
    printf("JSONElement{type='%s', value=", elem->type);
    if (elem->stringValue) {
        printf("%s", elem->stringValue);
    } else {
        printf("null");
    }
    printf("}\n");
}

int main() {
    // Test case 1: Simple object
    const char* test1 = "{\"name\": \"John\", \"age\": 30}";
    printf("Test 1: ");
    printJSONElement(parseAndGetRoot(test1));

    // Test case 2: Array
    const char* test2 = "[1, 2, 3, 4, 5]";
    printf("Test 2: ");
    printJSONElement(parseAndGetRoot(test2));

    // Test case 3: Nested object
    const char* test3 = "{\"person\": {\"name\": \"Alice\", \"age\": 25}, \"active\": true}";
    printf("Test 3: ");
    printJSONElement(parseAndGetRoot(test3));

    // Test case 4: String value
    const char* test4 = "\"Hello World\"";
    printf("Test 4: ");
    printJSONElement(parseAndGetRoot(test4));

    // Test case 5: Complex nested structure
    const char* test5 = "{\"users\": [{\"id\": 1, \"name\": \"Bob\"}, {\"id\": 2, \"name\": \"Carol\"}], \"count\": 2}";
    printf("Test 5: ");
    printJSONElement(parseAndGetRoot(test5));

    return 0;
}
