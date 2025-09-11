#include <stdio.h>
#include <json-c/json.h> // Requires json-c library

void deserializeJson(const char* json) {
    json_object* jobj = json_tokener_parse(json);
    if (jobj) {
        json_object* name = json_object_object_get(jobj, "name");
        json_object* age = json_object_object_get(jobj, "age");

        if (name && age) {
            printf("Name: %s\n", json_object_get_string(name));
            printf("Age: %d\n", json_object_get_int64(age));
        } else {
            printf("Invalid JSON\n");
        }

        json_object_put(jobj);
    } else {
        printf("Invalid JSON\n");
    }
}

int main() {
    const char* testCases[] = {
        "{\"name\":\"John\",\"age\":30}",
        "{\"name\":\"Alice\",\"age\":25}",
        "{\"name\":\"Bob\",\"age\":40}",
        "{\"name\":\"Charlie\",\"age\":35}",
        "{\"name\":\"David\",\"age\":20}"
    };

    for (int i = 0; i < 5; i++) {
        deserializeJson(testCases[i]);
    }

    return 0;
}